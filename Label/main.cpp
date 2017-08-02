#include "Label.h"
#include "../EventHandler/EventHandler.h"

using namespace std;

int main(void) {

	Label label(20, "Or Adar");
	label.setLocation({ 20, 30 });
	EventHandler Handler;
	Handler.run(label);
	return 0;
}