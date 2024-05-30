#pragma once
#include "Section.hpp"
#include <vector>

class SubSection : public Section
{
private:
    std::vector<Section*> sections;
    
    void printHelp();

public:
    SubSection();
    SubSection(std::string name, std::string help);
    ~SubSection();

    void addSection(Section* section);

    bool call(const std::string& command) override;
    std::string complete(const std::string& command) override;
};
