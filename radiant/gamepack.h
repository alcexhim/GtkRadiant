#ifndef _GAMEPACK_H_
#define _GAMEPACK_H_

#include "str.h"

/*!
   store information about custom .game xml attributes
 */

class CGamePackCustomAttribute {
  public:
    Str Name;
    Str Value;
};

/*!
   store information about installable game packs
 */

class CGamePack {
  public:
    bool HasCustomEngine;
    Str Title;
    Str GamePack;
    Str GameFilePath;
    
    vector<CGamePackCustomAttribute> CustomAttributes;
    
    static CGamePack* Load(Str iniFileName);
    
  protected:
    Str m_strIniFileName;
};

#endif // _GAMEPACK_H_