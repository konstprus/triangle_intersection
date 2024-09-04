#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>
#include <list>

#include "triangle3d.h"
#include "geometry_io.h"
#include "intersection_algorithms.h"

class TestRunner {
 public:
  TestRunner();
  void ParseString(const std::string& strLine);
  void PrepareReport();
  void WriteReport(std::ostream& os) const;

 private:
  bool CheckStream(size_t currentLine, const std::ostream& os);

  struct TestInfo {
    ti::Triangle3D tr1;
    ti::Triangle3D tr2;
    bool expectedValue;
    size_t lineNumberInFile;
    bool isValid{true};
  };

  enum class CurrentRarseStep {
    cs_ReadFirstTriangle, 
    cs_ReadSecondTriangle,
    cs_ReadExpectedResult
  };
  using TestInfoPtr = std::shared_ptr<TestInfo>;

  size_t currentLine;
  size_t doneTests;
  size_t failedTests;
  std::list<TestInfoPtr> testCollection;
  TestInfoPtr currentTest;
  CurrentRarseStep currentStep;
  std::stringstream reportStream;

};

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cerr << "The command line should contain the name of text file"
              << std::endl;
    return 1;
  }
  std::filesystem::path filePath(argv[1]);
  if (std::filesystem::exists(filePath)) {
    try {
      std::ifstream file(filePath);
      if (!file.is_open()) {
        std::cerr << "Could not open the file" << std::endl;
        return 1;
      }
      TestRunner runner;
      std::string strLine;
      while (std::getline(file, strLine)) {
        runner.ParseString(strLine);
      }
      runner.PrepareReport();
      runner.WriteReport(std::cout);
      file.close();
      return 0;
    } catch (const std::exception& ex) {
      std::cerr << "Error occured during parsing input file. Error message: "
                << ex.what() << std::endl;
      return 1;
    }
  }
  std::cerr << "Input doesn't exist" << std::endl;
  return 1;
}

TestRunner::TestRunner(): 
  currentLine(0), 
  doneTests(0), 
  failedTests(0),
  testCollection(),
  currentTest(nullptr), 
  currentStep(CurrentRarseStep::cs_ReadFirstTriangle) {}

void TestRunner::ParseString(const std::string& strLine) {
  currentLine++;
  if (strLine.empty() || strLine.starts_with('#')) {
    return;
  }
  std::stringstream strStream(strLine);
  try {
    switch (currentStep) {
      case TestRunner::CurrentRarseStep::cs_ReadFirstTriangle:
        currentTest = std::make_shared<TestInfo>();
        strStream >> currentTest->tr1;
        CheckStream(currentLine, strStream);
        currentStep = CurrentRarseStep::cs_ReadSecondTriangle;
        break;
      case TestRunner::CurrentRarseStep::cs_ReadSecondTriangle:
        if (currentTest->isValid) {
          strStream >> currentTest->tr2;
          CheckStream(currentLine, strStream);
        }
        currentStep = CurrentRarseStep::cs_ReadExpectedResult;
        break;
      case TestRunner::CurrentRarseStep::cs_ReadExpectedResult: 
        {
          if (currentTest->isValid) {
            std::string strBoolValue;
            strStream >> strBoolValue;
            if (strBoolValue == "true") {
              currentTest->expectedValue = true;
            } 
            else {
              currentTest->expectedValue = false;
            }
            currentTest->lineNumberInFile = currentLine;
            CheckStream(currentLine, strStream);
          }
          if (currentTest->isValid) {
            testCollection.push_back(currentTest);
          }
          currentTest.reset();
          currentStep = CurrentRarseStep::cs_ReadFirstTriangle;
        } 
        break;
      default:
        break;
    }
  } catch (std::exception& ex) {
    std::cerr << "Error occured during reading a line " << currentLine
              << "Error message : " << ex.what() << std::endl;
    if (currentTest != nullptr) {
      currentTest->isValid = false;
    }
  }

}

void TestRunner::PrepareReport() {
  reportStream << std::boolalpha;
  for (const auto& info : testCollection) {
    auto isIntersect = ti::IsIntersect(info->tr1, info->tr2);
    if (isIntersect != info->expectedValue) {
      reportStream << "line " << info->lineNumberInFile << ": expected "
                   << info->expectedValue << ", got " << isIntersect << std::endl;
      failedTests++;
    }
    doneTests++;
  }
  reportStream << "Tests done " << doneTests << "/" << failedTests << " failed" << std::endl;
}

void TestRunner::WriteReport(std::ostream& os) const {
  os << reportStream.str();
}

bool TestRunner::CheckStream(size_t currentLine, const std::ostream& os) { 
  if (os.fail()) {
    if (currentTest != nullptr && currentTest->isValid) {
      std::cerr << "Error occured during parsing line " << currentLine
                << ". Test # " << testCollection.size() + 1 << " will be missed."
                << std::endl;
      currentTest->isValid = false;
    }
    return false;
  }
  return true;
}
