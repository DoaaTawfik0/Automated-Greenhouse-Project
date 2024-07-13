# 👨🏻‍💻Automated-Greenhouse-Project
--

## Overview
The Greenhouse Project is an embedded system designed to automate the control of environmental conditions within a greenhouse. This project utilizes two microcontrollers to manage temperature, humidity, and lighting, ensuring optimal conditions for plant growth.

## Components
- **Microcontrollers**: Two microcontrollers for managing different sensors and actuators.
- **LM35 Sensor**: Measures the temperature inside the greenhouse.
- **Heater**: Activates if the temperature falls below 18°C.
- **Fan**: Activates if the temperature exceeds 25°C.
- **Soil Moisture Sensor**: Measures the humidity of the soil.
- **Water Pump**: Activates if the soil moisture level is low.
- **LDR Sensor**: Detects light levels to determine day/night cycles.
- **LEDs**: Turn on during the night to provide artificial lighting.
- **LCD Display**: Displays all sensor measurements in real-time.
- **Alarm**: For integating any error
## Features
1. **Temperature Control**:
   - The LM35 sensor continuously monitors the temperature.
   - If the temperature drops below 18°C, the heater is activated.
   - If the temperature rises above 25°C, the fan is activated.

2. **Soil Moisture Control**:
   - The soil moisture sensor monitors the humidity of the soil.
   - If the soil moisture level is low, the water pump is activated to irrigate the plants.

3. **Light Control**:
   - The LDR sensor detects the presence of sunlight.
   - If it is night, the LEDs are turned on to provide necessary lighting for the plants.

4. **Real-Time Monitoring**:
   - The LCD display shows real-time measurements from all sensors, allowing for easy monitoring of the greenhouse conditions.

5. **Alarm**: For integating any error or emegency state such that temperature below 15 or upper 30

## Installation
1. **Hardware Setup**:
   - Connect the LM35 sensor, soil moisture sensor, LDR sensor, heater, fan, water pump, LEDs, and LCD display to the respective microcontrollers.
   - Ensure all connections are secure and properly insulated.

2. **Software Setup**:
   - Upload the provided code to the microcontrollers.
   - Ensure the microcontrollers are properly programmed to handle the sensor inputs and control the actuators.

## GitHub Code Links

-  [LM35 Sensor Driver](https://github.com/DoaaTawfik0/Automated-Greenhouse-Project/tree/main/HAL/LM35)
  
- [Soil Moisture Sensor Driver](https://github.com/DoaaTawfik0/Automated-Greenhouse-Project/tree/main/HAL/Soil_Moisture)
  
- [LDR Sensor Driver](https://github.com/DoaaTawfik0/Automated-Greenhouse-Project/tree/main/HAL/LDR)
  
- [LCD Display Driver](https://github.com/DoaaTawfik0/Automated-Greenhouse-Project/tree/main/HAL/Character_LCD)

## Usage
- Once the system is set up, it will automatically monitor and control the greenhouse environment.
- Regularly check the sensors and actuators to ensure they are functioning correctly.
- Adjust the system parameters as needed to suit specific plant requirements.

## Contributing
- Contributions to improve the project are welcome. Please fork the repository and submit a pull request with your changes.

## License
- This project is licensed under the MIT License. See the LICENSE file for more details.

---

Feel free to customize this README file further to fit your specific project details! If you have any other questions or need additional help, just let me know. 😊




