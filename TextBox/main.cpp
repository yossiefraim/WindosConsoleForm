#include <string>
#include "../EventHandler/EventHandler.h"
#include "TextBox.h"
#include "../Panel/Panel.h"
using namespace std;


int main(int argc, char **argv)
{
	TextBox tName(20);
	Panel p(25, 50);
	tName.setValue("First Name:");
	tName.setBorder(BorderType::Double);
	tName.setBackGround(BackgroundColor::Red); 
	tName.setForeground(ForegroundColor::Cyan);
	Control::setFocus(&tName);
	p.setBorder(BorderType::Double);
	p.addControl(&tName, 10, 20);
	EventHandler Handler;
	Handler.run(p);
	return 0;
}