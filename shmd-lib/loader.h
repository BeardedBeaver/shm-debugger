#pragma once

#include <istream>
#include <vector>

class Loader {
public:
    explicit Loader(std::istream& stream);

    std::vector<char> load();

    int getFps() const;

private:
    std::istream& m_stream;
    int m_fps;
};
