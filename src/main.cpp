#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <fstream>
#include <limits>
using namespace std;

//Input Pipeline
string input_pipeline(){
    string seq_="", line;
    string filename;
    cout<<"Enter the File Name/Path: ";
    cin>>filename;
    ifstream inputFile(filename);
    while(getline(inputFile, line)){
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }
        seq_ += line;
    }
    inputFile.close();
    return seq_;
}


// Counting occurences of all the nucleotides
unordered_map<char, int> nucleotide_counter(string seq, int seq_len){
    unordered_map<char, int> nucleotide_count = {
        {'A', 0},
        {'G', 0},
        {'C', 0},
        {'T', 0}
    };

    int i = 0;

    while(i<seq_len){
        if (seq[i]=='A') nucleotide_count['A']++;
        else if (seq[i]=='G') nucleotide_count['G']++;
        else if (seq[i]=='C') nucleotide_count['C']++;
        else if (seq[i]=='T') nucleotide_count['T']++;
        i++;
    }

    return nucleotide_count;
}

// Reverse Complement Generator
string reverse_complement(string seq, int seq_len){
    string reverse_ = seq;
    int i = 0;
    while (i<seq_len){
        if (reverse_[i]=='A') reverse_[i] = 'T';
        else if(reverse_[i]=='G') reverse_[i] = 'C';
        else if(reverse_[i]=='C') reverse_[i] = 'G';
        else if(reverse_[i]=='T') reverse_[i] = 'A';
        i++;
    }
    reverse(reverse_.begin(), reverse_.end());    

    return reverse_;
}

// Skew Counter
float skew_counter(int n1=0, int n2=0){
    return (float)(n1-n2)/(n1+n2);
}

int main(){

    string seq = input_pipeline();
    int seq_len = seq.length();
    // cout<<seq<<endl;
    

    unordered_map<char, int> nucleotide_count = nucleotide_counter(seq, seq_len);

    // Total percentage of each nucleotide
    float A_percent = ((float)nucleotide_count['A']/seq_len)*100;
    float G_percent = ((float)nucleotide_count['G']/seq_len)*100;
    float C_percent = ((float)nucleotide_count['C']/seq_len)*100;
    float T_percent = ((float)nucleotide_count['T']/seq_len)*100;

    float AT_skew = skew_counter(nucleotide_count['A'], nucleotide_count['T']);
    float GC_skew = skew_counter(nucleotide_count['G'], nucleotide_count['C']);

    string reverse_compl = reverse_complement(seq, seq_len);

    string output;
    cout<<"Enter the Output File Name/Path: ";
    cin>>output;
    ofstream file(output, ios::app);
    file<<"\n\nAdenine: "<<nucleotide_count['A']<<"("<<A_percent<<"%)"<<endl;
    file<<"Guanine: "<<nucleotide_count['G']<<"("<<G_percent<<"%)"<<endl;
    file<<"Cytosine: "<<nucleotide_count['C']<<"("<<C_percent<<"%)"<<endl;
    file<<"Thymine: "<<nucleotide_count['T']<<"("<<T_percent<<"%)"<<endl;
    file<<"Total Base Pairs: "<<seq_len<<endl;

    // GC Content
    file<<"\nGC Content: "<<nucleotide_count['G']+nucleotide_count['C']<<"("<<G_percent+C_percent<<"%)"<<endl;
    file<<"AT Skew: "<<AT_skew<<endl;
    file<<"GC Skew: "<<GC_skew<<endl;

    file<<"\n\nReverse Complement: "<<reverse_compl<<"\n";
    file.close();
    



    return 0;
}
