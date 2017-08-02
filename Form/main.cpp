#include <string>
#include "../Panel/Panel.h"
#include "../CheckList/CheckList.h"
#include "../ComboBox/ComboBox.h"
#include "../Graphics/Graphics.h"
#include "../TextBox/TextBox.h"
#include "../RadioList/RadioList.h"
#include "../EventHandler/EventHandler.h"
#include "../NumericBox/NumericBox.h"
#include "../MessegeBox/MsgBox.h"

using namespace std;

struct MyListener : public MouseListener
{
	MyListener(Control &c) : _c(c) { }
	void mousePressed(Control& b, short x, short y, bool isLeft)
	{
		_c.show();
		Control::setFocus(&_c);
	}
private:
	Control &_c;
};


int main(void){

	Label lName(50, "First Name: ");
	Label lLastName(50, "Last Name: ");
	Label lCompany(50, "Company:");
	Label lSex(50, "Sex:");
	Label lFavoritesMovies(50, "Favorive Movies: ");
	Label lAge(50, "Age:");
	TextBox tName(50);
	tName.setValue("Gal");
	tName.setBorder(BorderType::Double);
	TextBox tLastName(50);
	tLastName.setValue("Amitai");
	tLastName.setBorder(BorderType::Double);
	ComboBox cCompany(50, { "DC", "Marvel", "WB","Sony","Paramount" });
	cCompany.setSelectedIndex(1);
	cCompany.setBorder(BorderType::Single);
	RadioList rSex(8, 50, { "Male", "Female" });
	rSex.setBorder(BorderType::Single);
	CheckList clMovies(11, 50, { "Captain America", "Batman", "Spiderman" });
	clMovies.selectIndex(1);
	clMovies.setBorder(BorderType::Double);
	NumericBox nAge(15, 18, 120);
	nAge.setValue(28);
	nAge.setBorder(BorderType::Single);

	MsgBox msgBox(15, 50);
	msgBox.hide();
	msgBox.setBorder(BorderType::Double);
	msgBox.setBackGround(BackgroundColor::White);
	msgBox.setForeground(ForegroundColor::Cyan);

	MyListener* listener = new MyListener(msgBox);
	Button bSubmit(10, "Submit");
	bSubmit.addListener(*listener);
	bSubmit.setBorder(BorderType::Double);


	Panel main(70, 100);
	main.addControl(&msgBox, 26, 40);
	main.addControl(&lName, 15, 3);
	main.addControl(&tName, 15, 5);
	main.addControl(&lLastName, 15, 8);
	main.addControl(&tLastName, 15, 10);
	main.addControl(&lCompany, 15, 13);
	main.addControl(&cCompany, 15, 15);
	main.addControl(&lSex, 15, 20);
	main.addControl(&rSex, 17, 22);
	main.addControl(&lFavoritesMovies, 15, 30);
	main.addControl(&clMovies, 15, 32);
	main.addControl(&bSubmit, 17, 45);
	Control::setFocus(&tName);
	EventHandler Handler;
	Handler.run(main);
	return 0;

}


//Created by Or Adar , Yossi Efraim, Gal Amitai and Uri Portnoy
//Method in Software Engineering
//Dr. Rash Amit, Mr. Algawi Asaf