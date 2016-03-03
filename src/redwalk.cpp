#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <list>
#include <map>

#include <redwalk.hpp>

static const std::string usage = 
"\
Usage: redwalk [OPTION]... [FILE]...\n\
Perform redwalk community detection on an undirected, unweighted graph.\n\
\n\
Mandatory arguments to long options are mandatory for short options too.\n\
  -o, --output=FILE      write the merge matrix to FILE\n\
                           default for FILE is \"merge.mat\"\n\
  -i, --input=FILE       file to read graph edgelist from\n\
  -k, --cutat=NUM        print the partition of NUM communities\n\
                           can be used multiple times\n\
  -q, --quiet            do not display progress\n\
  -v, --verbose          print lots of information\n\
  -h, --help             show this message and exit\n\
      --version          show version information and exit\n\
\n\
Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur placerat \n\
nisi ultrices, pretium libero quis, commodo mauris. Quisque vitae risus libero.\
";

void show_usage()
{
  std::cout << "redwalk v" << REDWALK_VERSION << "\n\n";
  std::cout << usage << "\n";
}

void quit_error(std::string msg, int err = 1)
{
  std::cerr << msg << std::endl;
  exit(err);
}

std::string bool_str(bool b)
{
  return (b) ? "true" : "false";
}

static std::map<std::string, char> opt_map = {
  {"-o", 'o'}, {"--output", 'o'}, 
  {"-i", 'i'}, {"--input", 'i'}, 
  {"-k", 'k'}, {"--cutat", 'k'},
  {"-q", 'q'}, {"--quiet", 'q'}, 
  {"-v", 'v'}, {"--verbose", 'v'}, 
  {"-h", 'h'}, {"--help", 'h'},
               {"--version", 'x'}
};

// OPTIONS STRUCT
struct
{
  std::list<unsigned long> k;
  std::string ifile  = "";
  std::string ofile  = "merge.mat";
  bool verbose       = false;
  bool quiet         = false;
} opt;

void print_opts()
{
  std::cout << "Input  : " << opt.ifile << "\n";
  std::cout << "Output : " << opt.ofile << "\n";
  std::cout << "Verbose: " << bool_str(opt.verbose) << "\n";
  std::cout << "Quiet  : " << bool_str(opt.quiet) << "\n";
  std::cout << "Print K: ";
  for(auto k : opt.k) { std:: cout << k << " "; }
  std::cout << std::endl;
}

int main(int argc, const char* argv[])
{
  //parse options
  for(int i = 0; i < argc; i++)
  {
    std::string arg(argv[i]);
    std::string val;
    if(i != (argc - 1))
      val = std::string(argv[i+1]);
    
    if(arg[0] == '-')
    {
      
      char copt = opt_map[arg];
      switch(copt)
      {
        case 'o':
          if(i == argc-1)
            quit_error("option -o (--output) needs an argument");
          opt.ofile = val;
          i++;
          break;
        case 'i':
          if(i == argc-1)
            quit_error("option -i (--input) needs an argument");
          opt.ifile = val;
          i++;
          break;
        case 'k':
          //check for another arg
          opt.k.push_back(std::stoul(val));
          i++;
          break;
        case 'q':
          opt.quiet = true;
          break;
        case 'v':
          opt.verbose = true;
          break;
        case 'h':
          show_usage();
          return 0;
        default:
        
          break;
      }
    }
  }
  
  opt.k.sort();
  print_opts();
  
  if(opt.ifile == "") {
    quit_error("error: no input file provided to read edgelist");
  }
  
  //open file and read graph (or read stdin)
  //TODO: if opt.ifile == "", read from stdin
  std::ifstream ifile(opt.ifile);
  if(!ifile)
  {
    std::cerr << "Error opening file to read: " << opt.ifile << "\n";
    return -1;
  }
  else
  {
  
  }
  ifile.close();
  
  //check graph
  
  //do community detection
  
  //open/create file for writing results (or print to stdout)
  std::ofstream ofile(opt.ofile);
  if(!ofile)
  {
    std::cerr << "Error opening file to write: " << opt.ofile << "\n";
    return -1;
  }
  else
  {
    //write the merge matrix (with heights) to the file
    ofile << "TODO\n";
    ofile.close();
  }
  
  
  //report and exit
  return 0;
}
