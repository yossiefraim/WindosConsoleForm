#include "RadioList.h"
#include "../EventHandler/EventHandler.h"

int main(VOID) {
	Panel p(25, 50);
	p.setLocation({ 10, 10 });
	p.setBorder(BorderType::Single);
	vector<string> strings;
	strings.push_back("Yosii");
	strings.push_back("Gal");
	strings.push_back("Uri");
	strings.push_back("Or");
	RadioList cName(14, 30, strings);
	cName.setBorder(BorderType::Double);
	Control::setFocus(&cName);
	cName.setBackGround(BackgroundColor::Green);
	p.addControl(&cName, 15, 15);
	EventHandler Handler;
	Handler.run(p);
	return 0;
}