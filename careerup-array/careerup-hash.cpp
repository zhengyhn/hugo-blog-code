#include <iostream>
#include <tr1/unordered_map>

int
main(void)
{
    using std::string;
    typedef std::tr1::unordered_map<string, int> HashMap;
    HashMap num;

    num["one"] = 1;
    num["two"] = 2;

    std::tr1::hash<string> hash_func = num.hash_function();
    for (HashMap::const_iterator i = num.begin(); i != num.end(); ++i) {
        std::cout << i->first << " -> " << i->second
                  << "(hash=" << hash_func(i->first) << ")" << std::endl;
    }
    
    return 0;
}
