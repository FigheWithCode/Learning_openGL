//
// Created by Gal on 9/14/26.
//

#ifndef LEARNOPENGL_EXERCISE_SHADER_H
#define LEARNOPENGL_EXERCISE_SHADER_H

#include<string>

class Exercise_Shader {
public:
    Exercise_Shader(const char* vertexPath,const char* fragmentPath);
    void use();
    unsigned int ID;
private:
    void CheckSuccess(unsigned int , std::string);
};


#endif //LEARNOPENGL_EXERCISE_SHADER_H
