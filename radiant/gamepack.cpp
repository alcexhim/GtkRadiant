#include "stdafx.h"
#include <glib.h>

#include "gamepack.h"

#include <stdio.h>
#include <stdlib.h>

CGamePack* CGamePack::Load( Str filename ) {
	CGamePack* pack = new CGamePack();
	FILE* f = fopen(filename.GetBuffer(), "r");
	
	Str w = "";
	Str propName = "";
	Str propValue = "";
	bool comment = false;
	
	while (!feof(f)) {
		char c = getc(f);
		if (c == '\n') {
			comment = false;
			propValue = w.GetBuffer();
			w = "";
			
			Sys_Printf(" %s = %s \n", propName.GetBuffer(), propValue.GetBuffer() );
			
			if (propName == "title") {
				pack->Title = propValue.GetBuffer();
			} else if (propName == "gamepack") {
				pack->GameFilePath = propValue.GetBuffer();
			}
			else if (propName != "" && propValue != "") {
				CGamePackCustomAttribute attr;
				attr.Name = propName.GetBuffer();
				attr.Value = propValue.GetBuffer();
				pack->CustomAttributes.push_back( attr );
			}
			
			propName = "";
			propValue = "";
			w = "";
		}
		else if (c == ';') {
			comment = true;
		}
		else if (!comment) {
			if (c == '=') {
				propName = w.GetBuffer();
				w = "";
			} else {
				w += c;
			}
		}
	}
	
	return pack;
}
