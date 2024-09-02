#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>
#include <list>

#include "triangle3d.h"
#include "geometry_io.h"
#include "intersection_algorithms.h"

class CheckRunner {
 public:
  CheckRunner();
  void ParseString(const std::string& strLine);
  void PrepareReport();
  void WriteReport(std::ostream& os) const;

 private:
  struct TriangleIntersectInfo {
    ti::Triangle3D tr1;
    ti::Triangle3D tr2;
    bool expectedValue;
    bool realValue;
    size_t lineNumberInFile;
  };

  enum class CurrentRarseStep {
    cs_ReadFirstTriangle, 
    cs_ReadSecondTriangle,
    cs_ReadExpectedResult
  };
  using InfoPtr = std::shared_ptr<TriangleIntersectInfo>;

  size_t currentLine;
  size_t doneTests;
  size_t failedTests;
  std::list<InfoPtr> inputInfoCollection;
  InfoPtr currentInfoStorage;
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
      CheckRunner runner;
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

CheckRunner::CheckRunner(): 
  currentLine(0), 
  doneTests(0), 
  failedTests(0),
  inputInfoCollection(),
  currentInfoStorage(nullptr), 
  currentStep(CurrentRarseStep::cs_ReadFirstTriangle) {}

void CheckRunner::ParseString(const std::string& strLine) {
  currentLine++;
  if (strLine.empty() || strLine.starts_with('#')) {
    return;
  }
  std::stringstream strStream(strLine);
  switch (currentStep) {
    case CheckRunner::CurrentRarseStep::cs_ReadFirstTriangle:
      currentInfoStorage = std::make_shared<TriangleIntersectInfo>();
      strStream >> currentInfoStorage->tr1;
      currentStep = CurrentRarseStep::cs_ReadSecondTriangle;
      break;
    case CheckRunner::CurrentRarseStep::cs_ReadSecondTriangle:
      strStream >> currentInfoStorage->tr2;
      currentStep = CurrentRarseStep::cs_ReadExpectedResult;
      break;
    case CheckRunner::CurrentRarseStep::cs_ReadExpectedResult:
    {
      std::string strBoolValue;
      strStream >> strBoolValue;
      if (strBoolValue == "true") {
        currentInfoStorage->expectedValue = true;
      } else {
        currentInfoStorage->expectedValue = false;
      }
      currentInfoStorage->lineNumberInFile = currentLine;
      inputInfoCollection.push_back(currentInfoStorage);
      currentInfoStorage.reset();
      currentStep = CurrentRarseStep::cs_ReadFirstTriangle;
    }
      break;
    default:
      break;
  }
}

void CheckRunner::PrepareReport() {
  reportStream << std::boolalpha;
  for (const auto& info : inputInfoCollection) {
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

void CheckRunner::WriteReport(std::ostream& os) const { os << reportStream.str(); }
