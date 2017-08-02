#include "ComboBox.h"
#include "../EventHandler/EventHandler.h"

int main(VOID) {
	Panel p(30, 60);
	p.setLocation({ 10, 10 });
	p.setBorder(BorderType::Single);
	vector<string> strings;
	strings.push_back("item1");
	strings.push_back("item2");
	strings.push_back("item3");
	strings.push_back("item4");
	strings.push_back("item5");
	ComboBox cName(40, strings);
	cName.setBorder(BorderType::Double);
	Control::setFocus(&cName);
	cName.setBackGround(BackgroundColor::Orange);
	cName.setForeground(ForegroundColor::Blue);
	p.addControl(&cName, 15, 15);
	EventHandler Handler;
	Handler.run(p);
	return 0;
}