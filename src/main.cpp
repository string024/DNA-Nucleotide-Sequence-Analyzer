#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <fstream>
#include <limits>
using namespace std;

//Input Pipeline
string input_pipeline(int option){
    string seq_="", line;
    if (option==1){
        string filename;
        cout<<"Enter the Exact File Name With Extension: ";
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
    else if(option==2){
        while(getline(cin, line)){
            seq_ += line;
        }
        return seq_;
    }
    return "";
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

    cout<<"\n\n=====================DNA Sequence Analyzer=====================\n\n";
    cout<<"Choose the Option:\n1. Input Fasta File\n2. Input Sequence Manually\n";
    cout<<"Option: ";

    int option;
    cin>>option;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if(option!=1 && option!=2){
        cerr<<"Enter Valid Input\n";
        return 1;
    }

    string seq = input_pipeline(option);
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

    
    cout<<"\n\nAdenine: "<<nucleotide_count['A']<<"("<<A_percent<<"%)"<<endl;
    cout<<"Guanine: "<<nucleotide_count['G']<<"("<<G_percent<<"%)"<<endl;
    cout<<"Cytosine: "<<nucleotide_count['C']<<"("<<C_percent<<"%)"<<endl;
    cout<<"Thymine: "<<nucleotide_count['T']<<"("<<T_percent<<"%)"<<endl;
    cout<<"Total Base Pairs: "<<seq_len<<endl;

    // GC Content
    cout<<"\nGC Content: "<<nucleotide_count['G']+nucleotide_count['C']<<"("<<G_percent+C_percent<<"%)"<<endl;
    cout<<"AT Skew: "<<AT_skew<<endl;
    cout<<"GC Skew: "<<GC_skew<<endl;

    cout<<"\n\nReverse Complement: ";
    cout<<reverse_compl<<endl;
    



    return 0;
}
