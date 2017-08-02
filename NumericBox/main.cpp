#include "../EventHandler/EventHandler.h"
#include "NumericBox.h"



int main(void) {
	Panel panel(25, 50);
	NumericBox box(20, 10, 100);
	box.setBackGround(BackgroundColor::Red);
	box.setForeground(ForegroundColor::White);
	panel.setLocation({ 3, 0 });
	panel.setBorder(BorderType::Double);
	panel.addControl(&box, 5, 5);
	EventHandler Handler;
	Handler.run(panel);
}