
#ifndef LORIS_MESSAGE_KEYVALUEPAIRCONTAINERINTERFACE_H_
#define LORIS_MESSAGE_KEYVALUEPAIRCONTAINERINTERFACE_H_

#include <vector>

class KeyValuePairContainerInterface {
public:
    virtual void AddKeyValuePair(unsigned int, float) = 0;
    virtual void AddKeyValuePair(unsigned int, int) = 0;

    //TODO Change the int to unsigned. - Andrew W
    virtual std::vector<int> GetKeys() = 0;
    virtual float GetFloat(int index) = 0;
    virtual int GetInt(int index) = 0;
};

#endif
