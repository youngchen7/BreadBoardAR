
#include <string>
#include <vector>
#include <iostream>

using namespace std;
using namespace Platform;

namespace instructAR{
	enum model {BREADBOARD, WIRE1, WIRE2, WIRE3, WIRE4, WIREBRIDGE, WIREPOWERL, WIREPOWERR, WIREGROUNDL, WIREGROUNDR, CAP1, LED1, RESISTOR1, 
		RESISTOR4220, POTENTIOMETER1K, RGBLED, RESISTOR4200, WIRE8, CALIBRATION, LEGOPLATE8X8};

	class Component
	{
	private:
		int m_value, m_exponent, m_xpos, m_ypos, m_zpos, m_orientation; //Orientation is degrees clockwise from north
		String^ m_name;
		String^ m_description;
		model m_model;

	public:
		Component(int _value, int _exponent, int _xpos, int _ypos, int _zpos, int _orientation, String^ _name, String^ _description, model _model)
			: m_value(_value), m_exponent(_exponent), m_xpos(_xpos), m_ypos(_ypos), m_zpos(_zpos) 
			, m_orientation(_orientation), m_name(_name), m_description(_description), m_model(_model)
		{}


		Component(int _value, int _exponent, int _xpos, int _zpos, int _orientation, String^ _name, String^ _description, model _model)
			: m_value(_value), m_exponent(_exponent), m_xpos(_xpos), m_zpos(_zpos)
			, m_orientation(_orientation), m_name(_name), m_description(_description), m_model(_model)
		{
			m_ypos = 0;
		}

		Component(int _xpos, int _zpos, int _orientation, String^ _name, model _model)
			: m_xpos(_xpos), m_zpos(_zpos), m_orientation(_orientation), m_name(_name), m_model(_model)
		{
			m_ypos = 0;
			m_description = "No Description Available";
			m_value = 0;
			m_exponent = 0;
		}

		Component(int _xpos, int _zpos, int _orientation, String^ _name, model _model, String^ _description)
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

		String^ getName()
		{
			return m_name;
		}

		String^ getDescription()
		{
			return m_description;
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
				break;
			}
			case 1:
			{
				Component gnd_wire(0, 0, 170, "gnd_wire", WIREGROUNDL, "Add a wire to ground");
				build.push_back(gnd_wire);

				Component res(0, 1, 90, "res", RESISTOR4220, "Add a ballast resistor for the LED");
				build.push_back(res);

				Component led(4, 2, 90, "led", LED1, "Add the LED");
				build.push_back(led);

				Component vcc_wire(5, 0, 185, "vcc_wire", WIREPOWERL, "Finally, complete the circuit by connecting it to VCC");
				build.push_back(vcc_wire);

				break;
			}
			case 2:
			{
				Component pwr_wire1(5, 9, 350, "pwr_wire1", WIREPOWERR, "[START] Connect a wire from VCC to row 6 for the blue LED");
				build.push_back(pwr_wire1);
				Component white_wire1(5, 6, 90, "white_wire1", WIRE3, "Add a short wire. This will connect the potentiometer to VCC.");
				build.push_back(white_wire1);
				Component pot1(7, 9, 90, "pot1", POTENTIOMETER1K, "Add a potentiometer as shown. This one will control the blue intensity.");
				build.push_back(pot1);
				Component res1(7, 7, 90, "res1", RESISTOR4200, "Add a ballast resistor (200 Ohms) for the blue LED");
				build.push_back(res1);
				Component white_wire2(11, 5, 90, "white_wire2", WIRE8, "Connect a length 8 wire. This will supply power from the potentiometer to the blue LED");
				build.push_back(white_wire2);

				Component pwr_wire2(12, 9, 10, "pwr_wire2", WIREPOWERR, "Connect a wire from VCC to row 13 for the blue LED.");
				build.push_back(pwr_wire2);
				Component white_wire3(12, 7, 90, "white_wire3", WIRE3, "Add a short wire, this will be for the green LED");
				build.push_back(white_wire3);
				Component pot2(15, 9, 90, "pot2", POTENTIOMETER1K, "Add the second potentiometer to control green intensity");
				build.push_back(pot2);
				Component res2(16, 7, 90, "res2", RESISTOR4200, "Add another ballast resistor, this time for the green LED");
				build.push_back(res2);

				Component pwr_wire3(28, 9, 10, "pwr_wire2", WIREPOWERR, "Connect a wire from VCC to row 29 for the red LED.");
				build.push_back(pwr_wire3);
				Component white_wire4(25, 7, 90, "white_wire4", WIRE3, "Add a short wire. This will connect the potentiometer to VCC.");
				build.push_back(white_wire4);
				Component pot3(25, 9, 90, "pot3", POTENTIOMETER1K, "Add the last potentiomter, to control red intensity");
				build.push_back(pot3);
				Component res3(22, 6, 90, "res3", RESISTOR4200, "Add the last ballast resistor for the red LED.");
				build.push_back(res3);


				Component gnd_wire1(21, 9, 350, "gnd_wire1", WIREGROUNDR, "Connect a wire from GND to row 22. This will connect to our common cathode RGB LED");
				build.push_back(gnd_wire1);
				Component RBGLED(20, 8, 90, "RGBLED", RGBLED, "Finally, add the RGB LED and connect to a 5V power source. The longer leg is colored black. [END]");
				build.push_back(RBGLED);
					
			}
			case 3: 
			{
				Component legoPlate(0, 0, 0, "RGBLED", LEGOPLATE8X8, "Lego Plate");
				build.push_back(legoPlate);
			}
			case 6:
			{
				Component calibration_ball(0, 0, 90, "ball", CALIBRATION);
				build.push_back(calibration_ball);
				break;
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