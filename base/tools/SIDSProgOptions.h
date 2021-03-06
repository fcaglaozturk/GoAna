/* 
 * File:   SIDSProgOptions.h
 * Author: winckler
 *
 * Created on March 11, 2015, 5:38 PM
 */

#ifndef FAIRPROGOPTIONS_H
#define	FAIRPROGOPTIONS_H

#include "SIDSLog.h"
#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <iterator>
#include <tuple>

template<class T>
    std::ostream& operator<<(std::ostream& os, const std::vector<T>& v)
    {
        std::copy(v.begin(), v.end(), std::ostream_iterator<T>(os, "  ")); 
        return os;
    }

namespace po = boost::program_options;

class SIDSProgOptions 
{
public:
    SIDSProgOptions(bool configfile=false);
    virtual ~SIDSProgOptions();

    int AddToCmdLineOptions(const po::options_description& optdesc);
    int AddToCfgFileOptions(const po::options_description& optdesc);
    int AddToVisibleOptions(const po::options_description& optdesc);
    int AddToEnvironmentOptions(const po::options_description& optdesc);

    template<typename T>
        void SetValue(const std::string& key, T& val)
        {
            try
            {
                if ( fvarmap.count(key) )
                    val=fvarmap[key].as<T>();
                else
                    SLOG(ERROR) <<"Key '"<< key <<"' not found in boost variable map";
            }
            catch(std::exception& e)
            {
                SLOG(ERROR) << "Problem in boost variable map for the key '" << key << "'";
                SLOG(ERROR) << e.what();
            }
        }
    
    template<typename T>
        T GetPar(const std::string& key)
        {
            T val;
            try
            {
                if ( fvarmap.count(key) )
                    val=fvarmap[key].as<T>();
                else
                    SLOG(ERROR) <<"Key '"<< key <<"' not found in boost variable map";
            }
            catch(std::exception& e)
            {
                SLOG(ERROR) << "Problem in boost variable map for the key '" << key << "'";
                SLOG(ERROR) << e.what();
            }
            return val;
        }

    int ParseCmdLine(const int argc, char** argv, const po::options_description& desc, po::variables_map& varmap, bool AllowUnregistered=false);
    int ParseCfgFile(const std::string& filename, const po::options_description& desc, po::variables_map& varmap, bool AllowUnregistered=false);
    int ParseEnvironment(const std::function<std::string(std::string)>&);
    virtual int ParseAll(const int argc, char** argv, bool AllowUnregistered=false)=0;

    virtual int PrintOptions();
    int PrintHelp();



protected:

    po::variables_map fvarmap;

    po::options_description fGenericDesc;
    po::options_description fConfigDesc;
    po::options_description fEnvironmentDesc;
    po::options_description fHiddenDesc;

    po::options_description fCmdline_options;
    po::options_description fConfig_file_options;
    po::options_description fVisible_options;

    int fVerboseLvl;
    std::string fConfigFile;
    boost::filesystem::path fHome_Env_Var;

    virtual int NotifySwitchOption();

private:

    // /////////////////////////////////////////////
    // Methods below are helper functions used in the PrintOptions method
    typedef std::tuple<std::string, std::string,std::string, std::string> VarValInfo_t;
    typedef std::map<std::string, VarValInfo_t > MapVarValInfo_t;

    VarValInfo_t Get_variable_value_info(const po::variable_value& var_val);

    template<typename T>
        std::string variable_value_to_string(const po::variable_value& var_val)
        {
            auto& value = var_val.value();
            std::ostringstream ostr;
            if(auto q = boost::any_cast< T >(&value))
                ostr<<*q;
            std::string val_str=ostr.str();
            return val_str;
        }

    static void Max(int &val, const int &comp)
    {
        if (comp>val)
            val=comp;
    }
};



#endif	/* FAIRPROGOPTIONS_H */

