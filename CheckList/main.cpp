#include "CheckList.h"
#include "../EventHandler/EventHandler.h"

int main(VOID){
	Panel p(25, 50);				//set location for the panel
	p.setLocation({ 10, 10 });
	p.setBorder(BorderType::Single);
	vector<string> strings;
	strings.push_back("Or");
	strings.push_back("Gal");
	strings.push_back("Yossi");
	strings.push_back("Uri");
	CheckList cName(14,30,strings);
	cName.setBorder(BorderType::Double);
	Control::setFocus(&cName);
	cName.setBackGround(BackgroundColor::Green);
	p.addControl(&cName, 15, 15);
	EventHandler Handler;
	Handler.run(p);
	return 0;
}