//
// Created by Gal on 9/15/26.
//

#ifndef LEARNOPENGL_TEXTURES_H
#define LEARNOPENGL_TEXTURES_H

#include<string>

class TEXTURES {
public:
    TEXTURES(std::string ,std::string);
    unsigned int ID;
    void use();
    void setInt(const std::string& name,int value) const;
private:
    void Debug(unsigned shader,std::string name);
};


#endif //LEARNOPENGL_TEXTURES_H
