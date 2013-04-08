// -------------------------------------------------------------
// The contents of this file may be distributed under the CC0
// license (http://creativecommons.org/publicdomain/zero/1.0/).
// Of course you may also distribute it under a more restrictive
// license, such as any of the OSI-approved licenses
// (http://www.opensource.org/licenses).
// -------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <exception>
#include <stdio.h>
#include <math.h>
#include <wchar.h>
#include <string>
#include <vector>
#include <fstream>
#ifdef WINDOWS
#	include <direct.h>
#endif
#include "../GClasses/GApp.h"
#include "../GClasses/GAssignment.h"
#include "../GClasses/GBezier.h"
#include "../GClasses/GBits.h"
#include "../GClasses/GBitTable.h"
#include "../GClasses/GCluster.h"
#include "../GClasses/GCrypto.h"
#include "../GClasses/GDecisionTree.h"
#include "../GClasses/GDiff.h"
#include "../GClasses/GDistribution.h"
#include "../GClasses/GEnsemble.h"
#include "../GClasses/GError.h"
#include "../GClasses/GFile.h"
#include "../GClasses/GFourier.h"
#include "../GClasses/GGaussianProcess.h"
#include "../GClasses/GGraph.h"
#include "../GClasses/GHashTable.h"
#include "../GClasses/GHiddenMarkovModel.h"
#include "../GClasses/GHillClimber.h"
#include "../GClasses/GKeyPair.h"
#include "../GClasses/GKNN.h"
#include "../GClasses/GLinear.h"
#include "../GClasses/GManifold.h"
#include "../GClasses/GMath.h"
#include "../GClasses/GMatrix.h"
#include "../GClasses/GMixtureOfGaussians.h"
#include "../GClasses/GNaiveBayes.h"
#include "../GClasses/GNaiveInstance.h"
#include "../GClasses/GNeighborFinder.h"
#include "../GClasses/GNeuralNet.h"
#include "../GClasses/GPolynomial.h"
#include "../GClasses/GPriorityQueue.h"
#include "../GClasses/GRand.h"
#include "../GClasses/GRayTrace.h"
#include "../GClasses/GRecommender.h"
#include "../GClasses/GRegion.h"
#include "../GClasses/GSelfOrganizingMap.h"
#include "../GClasses/GSocket.h"
#include "../GClasses/GSparseMatrix.h"
#include "../GClasses/GSpinLock.h"
#include "../GClasses/GStabSearch.h"
#include "../GClasses/GThread.h"
#include "../GClasses/GTime.h"
#include "../GClasses/GTransform.h"
#include "../GClasses/GDom.h"
#include "../GClasses/GVec.h"
#include "../GClasses/GReverseBits.h"

using namespace GClasses;
using std::cerr;
using std::cout;
using std::string;
using std::vector;

typedef void (*TestFunc)();



int sysExec(const char* szAppName, const char* szArgs, GPipe* pStdOut = NULL, GPipe* pStdErr = NULL, GPipe* pStdIn = NULL)
{
	string s = szAppName;
//#ifdef _DEBUG
//	s += "dbg";
//#endif
#ifdef WINDOWS
	s += ".exe";
#endif
	s += " ";
	s += szArgs;
	return GApp::systemExecute(s.c_str(), true, pStdOut, pStdErr, pStdIn);
}

class TempFileMaker
{
protected:
	const char* m_szFilename;

public:
	TempFileMaker(const char* szFilename, const char* szContents)
	: m_szFilename(szFilename)
	{
		if(szContents)
			GFile::saveFile(szContents, strlen(szContents), szFilename);
	}

	~TempFileMaker()
	{
		GFile::deleteFile(m_szFilename);
	}
};

namespace{
  /// A convenience class for making sequences
  ///
  /// Example: 
  ///
  /// \code
  /// (Seq<int>()+3+1+4+1+5).asVector();
  /// \endcode
  ///
  /// Will make a vector containing the elements 3,1,4,1, and 5
  template<class T>
  class Seq{						
    std::list<T> l;
  public:
    /// Create an empty sequence
    Seq(){  }

    /// Add \a next to this sequence
    /// \param next the item to add to the sequence
    /// \return this sequence after the append
    Seq<T>& operator+(T next){ l.push_back(next); return *this; }

    /// Return a vector that contains copies of the elements of this sequence
    /// \return a vector that contains copies of the elements of this sequence
    std::vector<T> asVector() const{ 
      return std::vector<T>(l.begin(), l.end()); }

    /// Return a list that contains copies of the elements of this sequence
    /// \return a list that contains copies of the elements of this sequence
    std::list<T> asList() const{ 
      return l; }
  };

  
};


///Return the golf dataset used in Mark Hall's dissertation
///"Correlation based feature selection for machine learning" in ARFF
///format. The nominal attributes have been replaced by integers
///representing my own ordinal interpretations of them.
std::string golf_arff_dataset(){
return
  "@RELATION Golf\n"
  "\n"
  "@ATTRIBUTE Play\treal\n"
  "@ATTRIBUTE Outlook\treal\n"
  "@ATTRIBUTE Temperature\treal\n"
  "@ATTRIBUTE Humidity\treal\n"
  "@ATTRIBUTE Wind\treal\n"
  "\n"
  "@DATA\n"
  "-1,1,1,1,-1\n"
  "-1,1,1,1,1\n"
  "1,-1,0,1,-1\n"
  "1,-1,-1,-1,-1\n"
  "1,0,-1,-1,1\n"
  "-1,1,0,1,-1\n"
  "1,1,-1,-1,-1\n"
  "1,1,0,-1,1\n"
  "1,0,0,1,1\n"
  "1,0,1,-1,-1\n"
  "1,0,1,1,-1\n"
  "1,-1,0,-1,-1\n"
  "-1,-1,0,1,1\n"
  "-1,-1,-1,-1,1\n";
}

///Runs the command line waffles_dimred attributeselector and returns the 
///output that was printed to stdout
///
///\param dataset the text of a file that will be used as input to
///               waffles_dimred attributeselector
///
///\param extension the filename extension (".arff", ".csv"
///                 (comma-separated), ".dat" (null separated) to use
///                 in the temporary file read in by waffles_dimred
///
///\param labels the indices of the attributes that are label
///              dimensions (0-based indices)
///
///\param ignored the indices of the attributes that are ignored
///              dimensions (0-based indices)
///
///\param retval the value returned by the command execution (non-zero
///              indicates failure)
///
///\return the output printed to stdout and standard error
///
std::string run_dimred_attributeselector(std::string dataset, 
					 std::string extension,
					 std::vector<int> labels, 
					 std::vector<int> ignored,
					 int& retval
					 ){
  using std::string;
  //Make the temp file in.extenson containing the requested data
  string tmpname = string("in")+extension;
  TempFileMaker inFile(tmpname.c_str(), dataset.c_str());

  // Build the command line
  string args;
  args += " attributeselector ";
  args += tmpname;
  std::vector<int>::const_iterator it;
  if(labels.size() > 0){
    it = labels.begin();
    args += " -labels "+ to_str(*it);
    for(++it; it != labels.end(); ++it){
      args += ","; args += to_str(*it);
    }
  }
  if(ignored.size() > 0){
    it = ignored.begin();
    args += " -ignore "+ to_str(*it);
    for(++it; it != ignored.end(); ++it){
      args += ","; args += to_str(*it);
    }
  }

  // Execute the command
  GPipe pipeStdOut;
  GPipe pipeStdErr;
  retval = sysExec("waffles_dimred", args.c_str(), &pipeStdOut, &pipeStdErr);
  
  return pipeStdOut.read()+pipeStdErr.read();
}


void test_dimred_attributeselector()
{
  int retval;
  TestEqual
    ("\nAttribute rankings from most salient to least salient. "
     "(Attributes are zero-indexed.)\n"
     "1 Outlook\n"
     "0 Play\n"
     "3 Humidity\n"
     "2 Temperature\n",
     run_dimred_attributeselector(golf_arff_dataset(),".arff",
				  (Seq<int>()).asVector(),
				  Seq<int>().asVector(),retval),
     "Unexpected output from golf dataset with no labels and no ignored");
  TestEqual
    (0, retval, "Golf dataset with no labels and no ignored "
     "failed command execution");

  TestEqual
    ("\nAttribute rankings from most salient to least salient. "
     "(Attributes are zero-indexed.)\n"
     "1 Outlook\n"
     "0 Play\n"
     "3 Humidity\n"
     "2 Temperature\n",
     run_dimred_attributeselector(golf_arff_dataset(),".arff",
				  (Seq<int>()+4).asVector(),
				  Seq<int>().asVector(),retval),
     "Unexpected output from golf dataset with labels=4 and no ignored");
  TestEqual
    (0, retval, "Golf dataset with no labels=4 and no ignored "
     "failed command execution");

  
  TestEqual
    ("\nAttribute rankings from most salient to least salient. "
     "(Attributes are zero-indexed.)\n"
     "3 Humidity\n"
     "1 Outlook\n"
     "2 Temperature\n"
     "4 Wind\n",
     run_dimred_attributeselector(golf_arff_dataset(),".arff",
				  (Seq<int>()+0).asVector(),
				  Seq<int>().asVector(),retval),
     "Unexpected output from golf dataset with labels=0 and no ignored");
  TestEqual
    (0, retval, "Golf dataset with no labels=0 and no ignored "
     "failed command execution");

  TestEqual
    ("\nAttribute rankings from most salient to least salient. "
     "(Attributes are zero-indexed.)\n"
     "3 Humidity\n"
     "4 Wind\n",
     run_dimred_attributeselector(golf_arff_dataset(),".arff",
				  (Seq<int>()+0).asVector(),
				  (Seq<int>()+1+2).asVector(),retval),
     "Unexpected output from golf dataset with labels=0 and ignored=1,2");
  TestEqual
    (0, retval, "Golf dataset with no labels=0 and ignored=1,2 "
     "failed command execution");

  TestContains
    ("is both ignored and used as a label",
     run_dimred_attributeselector(golf_arff_dataset(),".arff",
				  (Seq<int>()+1).asVector(),
				  (Seq<int>()+1+2).asVector(),retval),
     "Unexpected output from golf dataset with labels=1 and ignored=1,2");
  TestEqual
    (1, retval, "Golf dataset with no labels=1 and ignored=1,2 "
     "unexpectedly succeeded command execution");

  
  TestContains
    ("Unsupported file format",
     run_dimred_attributeselector(golf_arff_dataset(),".mat",
				  (Seq<int>()).asVector(),
				  (Seq<int>()).asVector(),retval),
     "Unexpected output from golf dataset with .mat input file");
  TestEqual
    (1, retval, "Golf dataset .mat input file "
     "unexpectedly succeeded command execution");  
}

///Runs the command line waffles_transform keeponlycolumns and returns the 
///output that was printed to stdout
///
///\param dataset the text of a file that will be used as input to
///               waffles_transform keeponlycolumns
///
///\param extension the filename extension (".arff", ".csv"
///                 (comma-separated), ".dat" (null separated) to use
///                 in the temporary file read in by waffles_transform
///
///\param tokeep the indices of the attributes that are supposed to be
///              kept
///
///\param retval the value returned by the command execution (non-zero
///              indicates failure)
///
///\return the output printed to stdout and standard error
///
std::string run_transform_keeponlycolumns(std::string dataset, 
					 std::string extension,
					 std::vector<int> tokeep, 
					 int& retval
					 ){
  using std::string;
  //Make the temp file in.extenson containing the requested data
  string tmpname = string("in")+extension;
  TempFileMaker inFile(tmpname.c_str(), dataset.c_str());

  // Build the command line
  string args;
  args += " keeponlycolumns ";
  args += tmpname;
  std::vector<int>::const_iterator it;
  if(tokeep.size() > 0){
    it = tokeep.begin();
    args += " "+ to_str(*it);
    for(++it; it != tokeep.end(); ++it){
      args += ","; args += to_str(*it);
    }
  }

  // Execute the command
  GPipe pipeStdOut;
  GPipe pipeStdErr;
  retval = sysExec("waffles_transform", args.c_str(), &pipeStdOut, &pipeStdErr);
  
  return pipeStdOut.read()+pipeStdErr.read();
}

void test_transform_keeponly()
{
  int retval;
  TestContains
    ("Unexpected end of arguments",
     run_transform_keeponlycolumns(golf_arff_dataset(),".arff",
				   (Seq<int>()).asVector(),retval),
     "Unexpected output from golf dataset with no columns listed");
  TestEqual
    (1, retval, "not having columns listed unexpectedly  "
     "succeeded command execution");

  TestContains
    ("Invalid column index: 5",
     run_transform_keeponlycolumns(golf_arff_dataset(),".arff",
				   (Seq<int>()+5).asVector(),retval),
     "Unexpected output from golf dataset when keeping only the non-existant "
     "column number 5");
  TestEqual
    (1, retval, "keeping only column 5 unexpectedly  "
     "succeeded command execution");

  TestEqual
    (
     "@RELATION Golf\n"
     "\n"
     "@ATTRIBUTE Outlook\treal\n"
     "\n"
     "@DATA\n"
     "1\n"
     "1\n"
     "-1\n"
     "-1\n"
     "0\n"
     "1\n"
     "1\n"
     "1\n"
     "0\n"
     "0\n"
     "0\n"
     "-1\n"
     "-1\n"
     "-1\n"
     ,run_transform_keeponlycolumns(golf_arff_dataset(),".arff",
				    (Seq<int>()+1).asVector(),retval),
     "Unexpected output from golf dataset keep only column 1");
  TestEqual
    (0, retval, "Keep only column 1 "
     "failed command execution");

  TestEqual
    (
     "@RELATION Golf\n"
     "\n"
     "@ATTRIBUTE Wind\treal\n"
     "\n"
     "@DATA\n"
     "-1\n"
     "1\n"
     "-1\n"
     "-1\n"
     "1\n"
     "-1\n"
     "-1\n"
     "1\n"
     "1\n"
     "-1\n"
     "-1\n"
     "-1\n"
     "1\n"
     "1\n"
     ,run_transform_keeponlycolumns(golf_arff_dataset(),".arff",
				    (Seq<int>()+4).asVector(),retval),
     "Unexpected output from golf dataset keep only column 4");
  TestEqual
    (0, retval, "Keep only column 4 "
     "failed command execution");

  TestEqual
    (
     "@RELATION Golf\n"
     "\n"
     "@ATTRIBUTE Play\treal\n"
     "@ATTRIBUTE Wind\treal\n"
     "\n"
     "@DATA\n"
     "-1,-1\n"
     "-1,1\n"
     "1,-1\n"
     "1,-1\n"
     "1,1\n"
     "-1,-1\n"
     "1,-1\n"
     "1,1\n"
     "1,1\n"
     "1,-1\n"
     "1,-1\n"
     "1,-1\n"
     "-1,1\n"
     "-1,1\n"
     ,run_transform_keeponlycolumns(golf_arff_dataset(),".arff",
				    (Seq<int>()+0+4).asVector(),retval),
     "Unexpected output from golf dataset keep only columns 0 and 4");
  TestEqual
    (0, retval, "Keep only columns 0 and 4 "
     "failed command execution");

  TestEqual
    (
     "@RELATION Golf\n"
     "\n"
     "@ATTRIBUTE Play\treal\n"
     "@ATTRIBUTE Outlook\treal\n"
     "@ATTRIBUTE Temperature\treal\n"
     "@ATTRIBUTE Humidity\treal\n"
     "@ATTRIBUTE Wind\treal\n"
     "\n"
     "@DATA\n"
     "-1,1,1,1,-1\n"
     "-1,1,1,1,1\n"
     "1,-1,0,1,-1\n"
     "1,-1,-1,-1,-1\n"
     "1,0,-1,-1,1\n"
     "-1,1,0,1,-1\n"
     "1,1,-1,-1,-1\n"
     "1,1,0,-1,1\n"
     "1,0,0,1,1\n"
     "1,0,1,-1,-1\n"
     "1,0,1,1,-1\n"
     "1,-1,0,-1,-1\n"
     "-1,-1,0,1,1\n"
     "-1,-1,-1,-1,1\n"
     ,run_transform_keeponlycolumns(golf_arff_dataset(),".arff",
				    (Seq<int>()+0+1+2+3+4).asVector(),retval),
     "Unexpected output from golf dataset keep all columns");
  TestEqual
    (0, retval, "Keep all columns "
     "failed command execution");

}

void test_transform_mergevert()
{
	// Make some input files
	TempFileMaker tempFile1("a.arff",
		"@RELATION test\n"
		"@ATTRIBUTE a1 continuous\n"
		"@ATTRIBUTE a2 { alice, bob }\n"
		"@ATTRIBUTE a3 { true, false }\n"
		"@DATA\n"
		"1.2, alice, true\n"
		"2.3, bob, false\n"
		);
	TempFileMaker tempFile2("b.arff",
		"@RELATION test\n"
		"@ATTRIBUTE a1 continuous\n"
		"@ATTRIBUTE a2 { charlie, bob }\n"
		"@ATTRIBUTE a3 { false, true }\n"
		"@DATA\n"
		"3.4, bob, true\n"
		"4.5, charlie, false\n"
		);

	// Execute the command
	GPipe pipeStdOut;
	if(sysExec("waffles_transform", "mergevert a.arff b.arff", &pipeStdOut) != 0)
		throw Ex("exit status indicates failure");
	char buf[512];
	size_t len = pipeStdOut.read(buf, 512);
	if(len == 512)
		throw Ex("need a bigger buffer");
	buf[len] = '\0';

	// Check the results
	GMatrix* pOutput = GMatrix::parseArff(buf, strlen(buf));
	Holder<GMatrix> hOutput(pOutput);
	GMatrix& M = *pOutput;
	if(M.rows() != 4 || M.cols() != 3)
		throw Ex("failed");
	if(M.relation()->valueCount(0) != 0)
		throw Ex("failed");
	if(M.relation()->valueCount(1) != 3)
		throw Ex("failed");
	if(M.relation()->valueCount(2) != 2)
		throw Ex("failed");
	std::ostringstream oss;
	GArffRelation* pRel = (GArffRelation*)M.relation().get();
	pRel->printAttrValue(oss, 1, 2.0);
	string s = oss.str();
	if(strcmp(s.c_str(), "charlie") != 0)
		throw Ex("failed");
	if(M[0][0] != 1.2 || M[1][0] != 2.3 || M[2][0] != 3.4 || M[3][0] != 4.5)
		throw Ex("failed");
	if(M[0][1] != 0 || M[1][1] != 1 || M[2][1] != 1 || M[3][1] != 2)
		throw Ex("failed");
	if(M[0][2] != 0 || M[1][2] != 1 || M[2][2] != 0 || M[3][2] != 1)
		throw Ex("failed");
}

void test_recommend_fillmissingvalues()
{
	// Make some input files
	TempFileMaker tempFile1("a.arff",
		"@RELATION test\n"
		"@ATTRIBUTE a1 { a, b, c }\n"
		"@ATTRIBUTE a2 continuous\n"
		"@ATTRIBUTE a3 { d, e, f }\n"
		"@ATTRIBUTE a4 { g, h, i }\n"
		"@DATA\n"
		"a, ?, f, i\n"
		"?, 2, ?, i\n"
		"b, ?, d, ?\n"
		"?, 4, ?, ?\n"
		"?, ?, e, g\n"
		"?, ?, e, ?\n"
		"a, ?, ?, h\n"
		"\n"
		);

	// Execute the command
	GPipe pipeStdOut;
	if(sysExec("waffles_recommend", "fillmissingvalues a.arff baseline", &pipeStdOut) != 0)
		throw Ex("exit status indicates failure");
	char buf[512];
	size_t len = pipeStdOut.read(buf, 512);
	if(len == 512)
		throw Ex("need a bigger buffer");
	buf[len] = '\0';

	// Check the results
	GMatrix* pOutput = GMatrix::parseArff(buf, strlen(buf));
	Holder<GMatrix> hOutput(pOutput);
	GMatrix& M = *pOutput;
	if(M.rows() != 7 || M.cols() != 4)
		throw Ex("failed");
	if(M[0][0] != 0)
		throw Ex("failed");
	if(M[0][1] != 3)
		throw Ex("failed");
	if(M[1][1] != 2)
		throw Ex("failed");
	if(M[2][1] != 3)
		throw Ex("failed");
	if(M[3][3] != 2)
		throw Ex("failed");
	if(M[4][0] != 0)
		throw Ex("failed");
	if(M[5][1] != 3)
		throw Ex("failed");
	if(M[6][2] != 1)
		throw Ex("failed");
	if(M[6][3] != 1)
		throw Ex("failed");
}

void test_parsearff_quoting(){
  const char* inputArff=
    "@relation 'squares of numbers'\n"
    "\n"
    "@attribute 'the number' real\n"
    "\n"
    "@attribute 'the square of the number' real\n"
    "\n"
    "@attribute exact {'is exact', inexact,is\\\\\\ exact}\n"
    "\n"
    "@data\n"
    "1,1,'is exact'\n"
    "2,4,is\\ exact\n"
    "1.414,2,inexact\n"
    "3,9,\"is exact\"\n"
    "4,16,\"is\\ exact\"\n"
    ;
    
  GMatrix* pOutput = GMatrix::parseArff(inputArff, strlen(inputArff));
  Holder<GMatrix> hOutput(pOutput);
  GMatrix& M = *pOutput;
  double expected_data[5][3]={{1,1,0},{2,4,0},{1.414,2,1},{3,9,0},{4,16,2}};
  GArffRelation* pRel = (GArffRelation*)M.relation().get();
  GArffRelation& R = *pRel;
  
  TestEqual(R.size(), (std::size_t)3, "Incorrect number of attributes");
  for(unsigned row = 0; row < 5; ++row){
    for(unsigned col = 0; col < 3; ++col){
      std::stringstream errdescr;
      errdescr << "Incorrect matrix entry [" << row << "][" << col << "]";
      TestEqual(M[row][col], expected_data[row][col], errdescr.str());
    }
  }
  TestEqual("squares of numbers", R.name(), "Incorrect relation name");
  TestEqual(true, R.areContinuous(0,2), 
	      "First or second attribute is not continuous");
  TestEqual(true, R.areNominal(2,1), "Third attribute is not nominal");

   std::stringstream val0, val1, val2;
   R.printAttrValue(val0, 2, 0);
   R.printAttrValue(val1, 2, 1);
   R.printAttrValue(val2, 2, 2);
   TestEqual("'is exact'",val0.str(),
	       "First value of third attribute incorrect name");
   TestEqual("inexact",val1.str(),
	       "Second value of third attribute incorrect name");
   TestEqual("'is\\ exact'",val2.str(),
	       "Third value of third attribute incorrect name");
  

  TestEqual("the number",R.attrName(0),"First attribute incorrect name");
  TestEqual("the square of the number",R.attrName(1),
	      "Second attribute incorrect name");
  TestEqual("exact",R.attrName(2),"Third attribute incorrect name");
  
}

void test_document_classification()
{
	{
		GFile::makeDir("class_spam");
		TempFileMaker tempFile1("class_spam/a.txt", "Buy now! Cheap Viagara. All of your problems are solved. For a limited time, Act now. Click here to for a free sample. You might already be a winner! Hurry, supplies are limited.");
		TempFileMaker tempFile2("class_spam/b.txt", "Congratulations, the Prince of Nigeria has selected you to be the benefactor of the sum of one million dollars! If you act now, he will immediately transfer this amount to your bank account.");
		TempFileMaker tempFile3("class_spam/c.txt", "Winner winner winner! You are the winner of the one million dollar sweepstakes. To collect one million dollars, click here now! Hurry, or it will be given to the runner up.");
		TempFileMaker tempFile4("class_spam/d.txt", "Dear bank customer, we regret to inform you that your account has been compromised. Please confirm your identity so that we may restore the one million dollars that has erroneously been stolen from your account.");
		TempFileMaker tempFile5("class_spam/e.txt", "Buy now! Just one dollar! Lap top computers. Cheap deals! Hurry. Supplies are limited. Mention this add and receive a free laptop with lifetime subscription.");
		TempFileMaker tempFile6("class_spam/f.txt", "Free samples! Great deals! discounts! coupons! Winner! Free money! One million dollars in prizes! Viagara! Hurry! Cheap!");

		GFile::makeDir("class_auto");
		TempFileMaker tempFile7("class_auto/a.txt", "Thank you for registering with our site. To confirm you identity, please follow this link.");
		TempFileMaker tempFile8("class_auto/b.txt", "Thank you for signing up for an account at foo.com. Your automatically generated password is ax58c90s3.");
		TempFileMaker tempFile9("class_auto/c.txt", "You, or someone claiming to be you has signed up for an account at yomamma.com. Please confirm your identity by clicking on the following link.");
		TempFileMaker tempFile10("class_auto/d.txt", "You are now registered with newssite.com. You may begin posting comments using your user name and password. Thank you for visiting us.");
		TempFileMaker tempFile11("class_auto/e.txt", "This is an automatically generated email. You have registered with somesite.com. Your new user name and password is found below. Thank you, and have a nice day.");
		TempFileMaker tempFile12("class_auto/f.txt", "A password has automatically been generated for you. To log in, please click on the link found below. Your password is asdfjkl");

		GFile::makeDir("class_ham");
		TempFileMaker tempFile13("class_ham/a.txt", "Dear Dr. Johnson, I am writing to inquire whether you will be attending the conference on document classification. I am seeking an opportunity to meet with you. Sincerely, Me.");
		TempFileMaker tempFile14("class_ham/b.txt", "Dear Bob, Are you there? I have been looking for you all over. I am on the fourth floor of the computer building. Didn't we agree to meet at 2:30pm?");
		TempFileMaker tempFile15("class_ham/c.txt", "Dear Susan, Thank you for baking me those delicious cinnamon rolls. I have never eaten anything so delicious in my entire life. You should become a professional chef. Sincerely, Me.");
		TempFileMaker tempFile16("class_ham/d.txt", "Bob, I cannot tell you how dissapointed I am that you have chosen to attend Dr. Johnson's conference. He is a poser, and I think you should talk to Susan about it first.");
		TempFileMaker tempFile17("class_ham/e.txt", "What do you mean? Of course I like cinnamon rolls. Everybody likes them! Unfortunately, my diet does not permit me to indulge in such frivoloties at this time. I sincerely hope you will make more when I am done with this.");
		TempFileMaker tempFile18("class_ham/f.txt", "Of course. How else would a slinky become lodged in the center of a giant cube of Jello? Meet me in the computer building five minutes before it starts, and we'll attend the conference together. See you then. --Bob");

		// Generate a sparse feature matrix and a corresponding dense label matrix
		{
			GPipe pipeIgnoreMe;
			if(sysExec("waffles_sparse", "docstosparsematrix class_ham class_auto class_spam", &pipeIgnoreMe) != 0)
				throw Ex("exit status indicates failure");
		}
		TempFileMaker tempFileFeatures("features.sparse", NULL);
		TempFileMaker tempFileLabels("labels.arff", NULL);

		// Shuffle the data
		GPipe pipeStdOut;
		if(sysExec("waffles_sparse", "shuffle features.sparse -seed 0 -labels labels.arff l2.arff", &pipeStdOut) != 0)
			throw Ex("exit status indicates failure");
		pipeStdOut.toFile("f2.sparse");
		TempFileMaker tempF2("f2.sparse", NULL);
		TempFileMaker tempL2("l2.arff", NULL);

		// Make a set of models
		vector<string> models;
		models.push_back("naivebayes");
		models.push_back("knn 3 -cosine");
		//models.push_back("knn 3 -pearson");
		//models.push_back("neuralnet");

		// Do cross-validation
		TempFileMaker tempFileTrainFeatures("train.sparse", NULL);
		TempFileMaker tempFileTestFeatures("test.sparse", NULL);
		TempFileMaker tempFileTrainLabels("train.arff", NULL);
		TempFileMaker tempFileTestLabels("test.arff", NULL);
		TempFileMaker tempFileModel("model.json", NULL);
		char buf[256];
		GMatrix results(18, models.size());
		for(size_t i = 0; i < 18; i++)
		{
			// Separate the test fold from the rest of the data
			string sArgs1 = "splitfold f2.sparse ";
			sArgs1 += to_str(i);
			sArgs1 += " 18";
			if(sysExec("waffles_sparse", sArgs1.c_str()) != 0)
				throw Ex("exit status indicates failure");
			string sArgs2 = "splitfold l2.arff ";
			sArgs2 += to_str(i);
			sArgs2 += " 18";
			if(sysExec("waffles_transform", sArgs2.c_str()) != 0)
				throw Ex("exit status indicates failure");

			// Train and test each model
			for(size_t j = 0; j < models.size(); j++)
			{
				// Train the model
				string sArgs = "train -seed 0 train.sparse train.arff ";
				sArgs += models[j];
				GPipe pipeStdOut2;
				if(sysExec("waffles_sparse", sArgs.c_str(), &pipeStdOut2) != 0)
					throw Ex("exit status indicates failure");
				pipeStdOut2.toFile("model.json");

				// Test the model
				GPipe pipeStdOut3;
				if(sysExec("waffles_sparse", "test -seed 0 model.json test.sparse test.arff", &pipeStdOut3) != 0)
					throw Ex("exit status indicates failure");
				size_t len = pipeStdOut3.read(buf, 256);
				if(len >= 256)
					throw Ex("Need a bigger buffer");
				buf[len] = '\0';
				double accuracy = atof(buf);
				results[i][j] = accuracy;
			}
		}
		double resultsNaiveBayes = results.mean(0);
		double resultsKnnCosine = results.mean(1);
		//double resultsKnnPearson = results.mean(2);
		if(resultsNaiveBayes < 0.83)
			throw Ex("failed");
		if(resultsKnnCosine < 0.88)
			throw Ex("failed");
		//if(resultsKnnPearson < 0.50)
		//	throw Ex("failed");
	}
	GFile::removeDir("class_ham");
	GFile::removeDir("class_auto");
	GFile::removeDir("class_spam");
}





class GTestHarness
{
protected:
	std::ostringstream m_testTimes;

	///A test will only be run if its name contains one of the
	///testNameSubstr strings.  Any string contains the empty string as
	///a substring, so the empty string matches all strings.
	std::list<std::string> m_testNameSubstr;
public:
	///Create a test harness that runs tests matching the substrings
	///passed on the command line. argc and argv are interpreted as if
	///they were the arguments to main.  If no substrings are given
	///(that is, no arguments are passed), all tests are run, as if one
	///argument of an empty string had been given.
	GTestHarness(int argc, char**argv)
	{
		//Make list of test names to match
 		if(argc < 2){ 
			m_testNameSubstr.push_back("");
		}else{
			for(int i = 1; i < argc; ++i){
				m_testNameSubstr.push_back(argv[i]);
			}
		}

		//Ready performance stats
		char buf[256];
		if(GApp::appPath(buf, 256, true) == -1)
			throw Ex("Failed to retrieve app path");
		if(chdir(buf) != 0)
			throw Ex("Failed to change the dir to the app folder");

		m_testTimes.flags(std::ios::showpoint | std::ios::skipws | std::ios::dec | std::ios::fixed | std::ios::left);
		m_testTimes.width(6);
		m_testTimes.precision(3);
		string s;
		GTime::appendTimeStampValue(&s, "-", " ", ":", false);
		m_testTimes << s;
	}

	~GTestHarness()
	{
		// Append the new measurements to perf.log
		std::ofstream os;
		bool exists = false;
		if(GFile::doesFileExist("perf.log"))
			exists = true;
		os.exceptions(std::ios::failbit|std::ios::badbit);
		try
		{
			os.open("perf.log", std::ofstream::out | std::ofstream::app);
		}
		catch(const std::exception&)
		{
			throw Ex("Error creating file: perf.log");
		}

		if(!exists)
		{
			os << "This file logs the running time of each unit test in seconds.\nThis might be useful for detecting performance regressions, etc.\nNote that these running times are affected by CPU load, so don't panic over a single blip.\nThis file is best viewed without line-wrapping.\n\n";
		}
		os << m_testTimes.str() << "\n";
	}

	void logTime(const char* szTestName, double secs)
	{
		m_testTimes << ",";

		// Record six letters of the test name (skipping the first one)
		size_t n = std::min((size_t)6, strlen(szTestName + 1));
		char buf[7];
		for(size_t j = 0; j < 6 - n; j++)
			buf[j] = ' ';
		memcpy(buf + 6 - n, szTestName + 1, n);
		buf[6] = '\0';
		m_testTimes << buf << "=";

		// Record the test time
		if(secs < 10) m_testTimes << "0";
		m_testTimes << secs;
	}

	///Return true if this testHarness will run a test named
	///testname.  You can also think about it as returning true
	///iff testname contains one of the strings passed on the
	///command line as a pattern which the test names must match.
	bool willRunTest(std::string testName) const{
		std::list<std::string>::const_iterator pat;
		const std::list<std::string>& pats = m_testNameSubstr;
		for(pat = pats.begin(); pat != pats.end(); ++pat){
			if(testName.find(*pat) != std::string::npos){
				return true;
			}
		}
		return false;
	}

	bool runTest(const char* szTestName, TestFunc pTest)
	{
		bool bPass = false;
		if(willRunTest(szTestName)){
			cout << szTestName;
			size_t nSpaces = (size_t)70 - strlen(szTestName);
			for( ; nSpaces > 0; nSpaces--)
				cout << " ";
			cout.flush();
			try
			{
				double beginTime = GTime::seconds();
				pTest();
				double endTime = GTime::seconds();
				logTime(szTestName, endTime - beginTime);
				cout << "Passed\n";
				bPass = true;
			}
			catch(const std::exception& e)
			{
				cout << "FAILED!!!\n";
				cout << e.what() << "\n\n";
			}
			catch(...)
			{
				cout << "FAILED!!!\n";
				cout << "A non-standard exception was thrown.\n\n";
			}
		}
		return bPass;
	}

	void runAllTests()
	{
		// Class tests
		runTest("GAgglomerativeClusterer", GAgglomerativeClusterer::test);
		runTest("GAssignment - linearAssignment", testLinearAssignment);
		runTest("GAssignment - GSimpleAssignment", GSimpleAssignment::test);
		runTest("GAtomicCycleFinder", GAtomicCycleFinder::test);
		runTest("GAttributeSelector", GAttributeSelector::test);
		runTest("GBag", GBag::test);
		runTest("GBagOfRecommenders", GBagOfRecommenders::test);
		runTest("GBaselineLearner", GBaselineLearner::test);
		runTest("GBaselineRecommender", GBaselineRecommender::test);
		runTest("GBezier", GBezier::test);
		runTest("GBits", GBits::test);
		runTest("GBitTable", GBitTable::test);
		runTest("GReverseBits", reverseBitsTest);
		runTest("GBrandesBetweenness", GBrandesBetweennessCentrality::test);
		runTest("GBucket", GBucket::test);
		runTest("GCategoricalSamplerBatch", GCategoricalSamplerBatch::test);
		runTest("GCompressor", GCompressor::test);
		runTest("GCoordVectorIterator", GCoordVectorIterator::test);
		runTest("GCrypto", GCrypto::test);
		runTest("GCycleCut", GCycleCut::test);
		runTest("GDecisionTree", GDecisionTree::test);
		runTest("GDiff", GDiff::test);
		runTest("GDijkstra", GDijkstra::test);
		runTest("GDom", GDom::test);
		runTest("GDynamicSystemStateAligner", GDynamicSystemStateAligner::test);
		runTest("GError.h - to_str", test_to_str);
		runTest("GFloydWarshall", GFloydWarshall::test);
		runTest("GFourier", GFourier::test);
		runTest("GGaussianProcess", GGaussianProcess::test);
		runTest("GGraphCut", GGraphCut::test);
		runTest("GHashTable", GHashTable::test);
		runTest("GHiddenMarkovModel", GHiddenMarkovModel::test);
		runTest("GIncrementalTransform", GIncrementalTransform::test);
		runTest("GInstanceRecommender", GInstanceRecommender::test);
		runTest("GKdTree", GKdTree::test);
		runTest("GKeyPair", GKeyPair::test);
		runTest("GKNN", GKNN::test);
		runTest("GLinearDistribution", GLinearDistribution::test);
		runTest("GLinearProgramming", GLinearProgramming::test);
		runTest("GLinearRegressor", GLinearRegressor::test);
		runTest("GManifold", GManifold::test);
		runTest("GMath", GMath::test);
		runTest("GMatrix", GMatrix::test);
		runTest("GMatrix::parseArff quoting", test_parsearff_quoting);
		runTest("GMatrixFactorization", GMatrixFactorization::test);
		runTest("GMeanMarginsTree", GMeanMarginsTree::test);
		runTest("GMixtureOfGaussians", GMixtureOfGaussians::test);
		runTest("GNaiveBayes", GNaiveBayes::test);
		runTest("GNaiveInstance", GNaiveInstance::test);
		runTest("GNeuralNet", GNeuralNet::test);
		runTest("GNeuralNetPseudoInverse", GNeuralNetPseudoInverse::test);
		runTest("GNonlinearPCA", GNonlinearPCA::test);
		runTest("GPackageServer", GPackageServer::test);
		runTest("GPCARotateOnly", GPCARotateOnly::test);
		runTest("GPolynomial", GPolynomial::test);
		runTest("GPriorityQueue", GPriorityQueue::test);
		runTest("GProbeSearch", GProbeSearch::test);
		runTest("GRand", GRand::test);
		runTest("GRandMersenneTwister", GRandMersenneTwister::test);
		runTest("GRandomForest", GRandomForest::test);
		runTest("GRelation", GRelation::test);
		runTest("GResamplingAdaBoost", GResamplingAdaBoost::test);
		runTest("GReservoirNet", GReservoirNet::test);
		runTest("GRunningCovariance", GRunningCovariance::test);
		runTest("GSelfOrganizingMap", GSelfOrganizingMap::test);
		runTest("GShortcutPruner", GShortcutPruner::test);
		runTest("GSparseClusterRecommender", GSparseClusterRecommender::test);
		runTest("GSparseMatrix", GSparseMatrix::test);
		runTest("GSpinLock", GSpinLock::test);
		runTest("GSubImageFinder", GSubImageFinder::test);
		runTest("GSubImageFinder2", GSubImageFinder2::test);
		runTest("GSupervisedLearner", GSupervisedLearner::test);
		runTest("GVec", GVec::test);

		string s = "waffles_learn";
#ifdef WIN32
		s += ".exe";
#endif

#ifdef WINDOWS
		bool runCommandLineTests = true;
#else
#	ifdef __linux__
		bool runCommandLineTests = true;
#	else
		bool runCommandLineTests = false; // I don't have the test-harness for the command-line apps working on OSX yet
#	endif
#endif
		if(runCommandLineTests)
		{
			if(GFile::doesFileExist(s.c_str()))
			{
				// Command-line tests
				runTest("waffles_transform mergevert", test_transform_mergevert);
				runTest("waffles_recommend fillmissingvalues", test_recommend_fillmissingvalues);
#ifndef WINDOWS
				runTest("waffles_transform keeponlycolumns", test_transform_keeponly);
				runTest("waffles_dimred attributeselector", test_dimred_attributeselector);
				runTest("document classification", test_document_classification);
#endif
			}
			else
				cout << "Skipping the command-line tool tests because the optimized command-line tools have not yet been built.\n";
		}

			cout << "Done.\n";
			cout.flush();
	}
};

int main(int argc, char *argv[])
{
	GApp::enableFloatingPointExceptions();

	if(argc < 2){
	  std::cout << 
	    "You can run only specific tests by passing strings that must be "
	    "substrings of \nthe test names on the command line\n";
	}

	int nRet = 0;
	try
	{
		GTestHarness harness(argc, argv);
		harness.runAllTests();
	}
	catch(const std::exception& e)
	{
		cerr << e.what() << "\n";
		nRet = 1;
	}

	return nRet;
}

