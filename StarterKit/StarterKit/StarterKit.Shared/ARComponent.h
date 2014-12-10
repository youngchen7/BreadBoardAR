
#include <string>
#include <vector>
#include <iostream>

using namespace std;

namespace instructAR{
	enum model {BREADBOARD, WIRE1, WIRE2, WIRE3, WIRE4, WIREBRIDGE, WIREPOWERL, WIREPOWERR, WIREGROUNDL, WIREGROUNDR, CAP1, LED1, RESISTOR1, 
		RESISTOR4220, POTENTIOMETER1K, RGBLED, RESISTOR4200, WIRE8, CALIBRATION};

	class Component
	{
	private:
		int m_value, m_exponent, m_xpos, m_ypos, m_zpos, m_orientation; //Orientation is degrees clockwise from north
		string m_name, m_description;
		model m_model;

	public:
		Component(int _value, int _exponent, int _xpos, int _ypos, int _zpos, int _orientation, string _name, string _description, model _model)
			: m_value(_value), m_exponent(_exponent), m_xpos(_xpos), m_ypos(_ypos), m_zpos(_zpos) 
			, m_orientation(_orientation), m_name(_name), m_description(_description), m_model(_model)
		{}


		Component(int _value, int _exponent, int _xpos, int _zpos, int _orientation, string _name, string _description, model _model)
			: m_value(_value), m_exponent(_exponent), m_xpos(_xpos), m_zpos(_zpos)
			, m_orientation(_orientation), m_name(_name), m_description(_description), m_model(_model)
		{
			m_ypos = 0;
		}

		Component(int _xpos, int _zpos, int _orientation, string _name, model _model)
			: m_xpos(_xpos), m_zpos(_zpos), m_orientation(_orientation), m_name(_name), m_model(_model)
		{
			m_ypos = 0;
			m_description = "No Description Available";
			m_value = 0;
			m_exponent = 0;
		}

		Component(int _xpos, int _zpos, int _orientation, string _name, model _model, string _description)
			: m_xpos(_xpos), m_zpos(_zpos), m_orientation(_orientation), m_name(_name), m_model(_model), m_description(_description)
		{
			m_ypos = 0;
			m_value = 0;
			m_exponent = 0;
		}


		int getX()
		{
			return m_xpos;
		}

		int getY()
		{
			return m_ypos;
		}

		int getZ()
		{
			return m_zpos;
		}

		int getOrientation()
		{
			return m_orientation;
		}

		model getModel()
		{
			return m_model;
		}

		string getName()
		{
			return m_name;
		}


	};

	class componentsFactory
	{
		public:

		componentsFactory(){}

		vector<Component> createBuild(int ID)
		{
			vector<Component> build;
			switch(ID)
			{
			case -1: //testing purposes
			{
				Component rgbLED(1, 1, 90, "rgbLED", RGBLED);
				build.push_back(rgbLED);
				
				Component res(0, 6, 90, "res", RESISTOR4220);
				build.push_back(res);

				Component wire(10, 5, 90, "pot", POTENTIOMETER1K);
				build.push_back(wire);

				Component cap(28, 6, 90, "cap", CAP1);
				build.push_back(cap);

				Component res2(2, 8, 90, "res", RESISTOR4200);
				build.push_back(res2);

				break;
			}
			case 0:
			{
				Component calibration_ball(0, 0, 90, "ball", CALIBRATION);
				build.push_back(calibration_ball);
			}
			case 1:
			{
				Component gnd_wire(0, 0, 170, "gnd_wire", WIREGROUNDL);
				build.push_back(gnd_wire);

				Component res(0, 1, 90, "res", RESISTOR4220);
				build.push_back(res);

				Component led(4, 2, 90, "led", LED1);
				build.push_back(led);

				Component vcc_wire(5, 0, 185, "vcc_wire", WIREPOWERL);
				build.push_back(vcc_wire);

				break;
			}
			case 2:
			{
				Component pwr_wire1(5, 9, 350, "pwr_wire1", WIREPOWERR);
				build.push_back(pwr_wire1);
				Component white_wire1(5, 6, 90, "white_wire1", WIRE3);
				build.push_back(white_wire1);
				Component pot1(7, 9, 90, "pot1", POTENTIOMETER1K);
				build.push_back(pot1);
				Component res1(7, 7, 90, "res1", RESISTOR4200);
				build.push_back(res1);
				Component white_wire2(11, 5, 90, "white_wire2", WIRE8);
				build.push_back(white_wire2);

				Component pwr_wire2(12, 9, 10, "pwr_wire2", WIREPOWERR);
				build.push_back(pwr_wire2);
				Component white_wire3(12, 7, 90, "white_wire3", WIRE3);
				build.push_back(white_wire3);
				Component pot2(15, 9, 90, "pot2", POTENTIOMETER1K);
				build.push_back(pot2);
				Component res2(16, 7, 90, "res2", RESISTOR4200);
				build.push_back(res2);

				Component pwr_wire3(28, 9, 10, "pwr_wire2", WIREPOWERR);
				build.push_back(pwr_wire3);
				Component white_wire4(25, 7, 90, "white_wire4", WIRE3);
				build.push_back(white_wire4);
				Component pot3(25, 9, 90, "pot3", POTENTIOMETER1K);
				build.push_back(pot3);
				Component res3(22, 6, 90, "res3", RESISTOR4200);
				build.push_back(res3);


				Component gnd_wire1(21, 9, 350, "gnd_wire1", WIREGROUNDR);
				build.push_back(gnd_wire1);
				Component RBGLED(20, 8, 90, "RGBLED", RGBLED);
				build.push_back(RBGLED);
					
			}

			default:
				return build;
				break;
			}

			return build;
		}
	};

}

/*
int main()
{
    instructAR::componentsFactory my_factory;
    vector<instructAR::Component> my_build = my_factory.createBuild(0);
    cout << my_build.size() << endl;
    cout << my_build.at(3).getName() << endl;
    
    
    return 1;
}
*/