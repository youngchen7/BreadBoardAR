
#include <string>
#include <vector>
#include <iostream>

using namespace std;

namespace instructAR{
	enum model {BREADBOARD, WIRE1, WIRE2, WIRE3, WIRE4, WIREBRIDGE, WIREPOWERL, WIREPOWERR, WIREGROUNDL, WIREGROUNDR, CAP1, LED1, RESISTOR1};

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

		Component(int _xpos, int _zpos, int _orientation, string _name, model _model)
			: m_xpos(_xpos), m_zpos(_zpos), m_orientation(_orientation), m_name(_name), m_model(_model)
		{
			m_ypos = 0;
			m_description = "No Description Available";
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
				case 0:
				{
					Component gnd_wire(0, 0, 170, "gnd_wire", WIREGROUNDL);
					build.push_back(gnd_wire);

					Component res(0, 1, 90, "res", RESISTOR1);
					build.push_back(res);

					Component led(2, 2, 90, "led", LED1);
					build.push_back(led);

					Component vcc_wire(3, 0, 170, "vcc_wire", WIREPOWERL);
					build.push_back(vcc_wire);

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