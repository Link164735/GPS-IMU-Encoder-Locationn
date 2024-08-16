#include <iostream>
#include <fstream>
#include <sstream>
#include "fusion.hpp"
#include "ekf.hpp"

int main(int argc, const char * argv[])
{

    Fusion fusion(2.0, 0.5, 0.1, 0.01, 0.02, 0.001, 0.005, 0.0, 0.0, false);

    std::ifstream ip("../data.csv");
    if (!ip.is_open())
    {
        std::cerr << "Failed to open the data file";
        return EXIT_FAILURE;
    }

    std::string str;
    std::getline(ip, str);

    while (std::getline(ip, str))
    {
        std::istringstream iss(str);
        std::string token;
        double date, time, millis, ax, ay, az, rollrate, pitchrate, yawrate, roll, pitch, yaw, \
        speed, course, lat, lon, alt, pdop, hdop, vdop, epe, fix, satellites_view, satellites_used, temp;

        
        std::getline(iss, token, ','); date = std::stod(token); // date
        std::getline(iss, token, ','); time = std::stod(token); // time
        std::getline(iss, token, ','); millis = std::stod(token); // millis
        std::getline(iss, token, ','); ax = std::stod(token); // ax
        std::getline(iss, token, ','); ay = std::stod(token); // ay
        std::getline(iss, token, ','); az = std::stod(token); // az
        std::getline(iss, token, ','); rollrate = std::stod(token); // rollrate
        std::getline(iss, token, ','); pitchrate = std::stod(token); // pitchrate
        std::getline(iss, token, ','); yawrate = std::stod(token); // yawrate
        std::getline(iss, token, ','); roll = std::stod(token); // roll
        std::getline(iss, token, ','); pitch = std::stod(token); // pitch
        std::getline(iss, token, ','); yaw = std::stod(token); // yaw
        std::getline(iss, token, ','); speed = std::stod(token); // speed
        std::getline(iss, token, ','); course = std::stod(token); // course
        std::getline(iss, token, ','); lat = std::stod(token); // latitude
        std::getline(iss, token, ','); lon = std::stod(token); // longitude
        std::getline(iss, token, ','); alt = std::stod(token); // altitude
        std::getline(iss, token, ','); pdop = std::stod(token); // pdop
        std::getline(iss, token, ','); hdop = std::stod(token); // hdop
        std::getline(iss, token, ','); vdop = std::stod(token); // vdop
        std::getline(iss, token, ','); epe = std::stod(token); // epe
        std::getline(iss, token, ','); fix = std::stod(token); // fix
        std::getline(iss, token, ','); satellites_view = std::stod(token); // satellites_view
        std::getline(iss, token, ','); satellites_used = std::stod(token); // satellites_used
        std::getline(iss, token, ','); temp = std::stod(token); // temp

        
        Eigen::VectorXd raw_data(6);
        raw_data << lat, lon, speed, yawrate, rollrate, pitchrate;
        
        DataPoint data;
        data.set(time, DataPointType::GPS, raw_data);

        fusion.process(data);

        Eigen::VectorXd state = fusion.get_resulting_state();
        Eigen::VectorXd reslut = state.transpose();
        std::cout << "Estimated State: " << " 坐标：("<< reslut[0] <<","<< reslut[1] << ") " << \
        " 偏航角: "<< reslut[2] <<" 速度: "<< reslut[3] << " 偏航率: "<< reslut[4] << \
        " 加速度: "<< reslut[5] << std::endl;
    }

    ip.close();
    return 0;
}
