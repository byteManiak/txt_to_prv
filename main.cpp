#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

void printUsage() { std::cout << "Usage: txt_to_prv src_file dest_file.\n"; }

int main(int argc, char **argv)
{
    if(argc!=3) { printUsage(); return 1; }
    std::ifstream src(argv[1]);
    std::ofstream dest(argv[2]);

    std::string buf;
    std::string prev_channel;
    while(std::getline(src, buf, '\n'))
    {
        std::stringstream t(buf);
        std::string time, name, channel;
        std::getline(t, time, '-');
        std::getline(t, buf, '\t');
        std::getline(t, name, '\t');
        std::getline(t, channel, '\n');
        if(channel!=prev_channel && channel.size()>0)
        {
            prev_channel = channel;
            std::transform(channel.begin(), channel.end(),channel.begin(), ::toupper);
            dest << "!insert \"" << channel << "\"\n";
        }
        if(time.size()>0 && name.size()>0)
        {
            std::transform(time.begin(), time.end(), time.begin(), ::toupper);
            std::transform(name.begin(), name.end(), name.begin(), ::toupper);
            dest << time << ' ' << name << '\n';
        }
    }
    return 0;
}
