//
// Created by Gal on 9/14/26.
//

#ifndef LEARNOPENGL_SHADER_H
#define LEARNOPENGL_SHADER_H

#include<string>

class SHADER {
public:
    unsigned int ID;

    SHADER(const char* vertexpath,const char* fragpath);
    void use();
private:
    void Debug(unsigned int shader,std::string name);
};


#endif //LEARNOPENGL_SHADER_H
