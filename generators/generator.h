#pragma once

class Generator {
  public:
    virtual ~Generator() { }
    virtual Grid* generate(int, int) = 0;
};
