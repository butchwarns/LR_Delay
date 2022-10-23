/* ------------------------------------------------------------
name: "delay"
Code generated with Faust 2.41.1 (https://faust.grame.fr)
Compilation options: -a faustMinimal.h -lang cpp -i -cn Delay -es 1 -mcd 16 -double -ftz 0
------------------------------------------------------------ */

#ifndef  __Delay_H__
#define  __Delay_H__

#include <cmath>
#include <cstring>

/************************** BEGIN MapUI.h ******************************
 FAUST Architecture File
 Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ***********************************************************************/

#ifndef FAUST_MAPUI_H
#define FAUST_MAPUI_H

#include <vector>
#include <map>
#include <string>
#include <stdio.h>

/************************** BEGIN UI.h *****************************
 FAUST Architecture File
 Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ********************************************************************/

#ifndef __UI_H__
#define __UI_H__

/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2018 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 ************************************************************************
 ************************************************************************/

#ifndef __export__
#define __export__

#define FAUSTVERSION "2.41.1"

// Use FAUST_API for code that is part of the external API but is also compiled in faust and libfaust
// Use LIBFAUST_API for code that is compiled in faust and libfaust

#ifdef _WIN32
    #pragma warning (disable: 4251)
    #ifdef FAUST_EXE
        #define FAUST_API
        #define LIBFAUST_API
    #elif FAUST_LIB
        #define FAUST_API __declspec(dllexport)
        #define LIBFAUST_API __declspec(dllexport)
    #else
        #define FAUST_API
        #define LIBFAUST_API 
    #endif
#else
    #ifdef FAUST_EXE
        #define FAUST_API
        #define LIBFAUST_API
    #else
        #define FAUST_API __attribute__((visibility("default")))
        #define LIBFAUST_API __attribute__((visibility("default")))
    #endif
#endif

#endif

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

/*******************************************************************************
 * UI : Faust DSP User Interface
 * User Interface as expected by the buildUserInterface() method of a DSP.
 * This abstract class contains only the method that the Faust compiler can
 * generate to describe a DSP user interface.
 ******************************************************************************/

struct Soundfile;

template <typename REAL>
struct FAUST_API UIReal {
    
    UIReal() {}
    virtual ~UIReal() {}
    
    // -- widget's layouts
    
    virtual void openTabBox(const char* label) = 0;
    virtual void openHorizontalBox(const char* label) = 0;
    virtual void openVerticalBox(const char* label) = 0;
    virtual void closeBox() = 0;
    
    // -- active widgets
    
    virtual void addButton(const char* label, REAL* zone) = 0;
    virtual void addCheckButton(const char* label, REAL* zone) = 0;
    virtual void addVerticalSlider(const char* label, REAL* zone, REAL init, REAL min, REAL max, REAL step) = 0;
    virtual void addHorizontalSlider(const char* label, REAL* zone, REAL init, REAL min, REAL max, REAL step) = 0;
    virtual void addNumEntry(const char* label, REAL* zone, REAL init, REAL min, REAL max, REAL step) = 0;
    
    // -- passive widgets
    
    virtual void addHorizontalBargraph(const char* label, REAL* zone, REAL min, REAL max) = 0;
    virtual void addVerticalBargraph(const char* label, REAL* zone, REAL min, REAL max) = 0;
    
    // -- soundfiles
    
    virtual void addSoundfile(const char* label, const char* filename, Soundfile** sf_zone) = 0;
    
    // -- metadata declarations
    
    virtual void declare(REAL* zone, const char* key, const char* val) {}
    
    // To be used by LLVM client
    virtual int sizeOfFAUSTFLOAT() { return sizeof(FAUSTFLOAT); }
};

struct FAUST_API UI : public UIReal<FAUSTFLOAT> {
    UI() {}
    virtual ~UI() {}
};

#endif
/**************************  END  UI.h **************************/
/************************** BEGIN PathBuilder.h **************************
 FAUST Architecture File
 Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __PathBuilder__
#define __PathBuilder__

#include <vector>
#include <set>
#include <map>
#include <string>
#include <algorithm>
#include <regex>


/*******************************************************************************
 * PathBuilder : Faust User Interface
 * Helper class to build complete hierarchical path for UI items.
 ******************************************************************************/

class FAUST_API PathBuilder {

    protected:
    
        std::vector<std::string> fControlsLevel;
        std::vector<std::string> fFullPaths;
        std::map<std::string, std::string> fFull2Short;  // filled by computeShortNames()
    
        /**
         * @brief check if a character is acceptable for an ID
         *
         * @param c
         * @return true is the character is acceptable for an ID
         */
        bool isIDChar(char c) const
        {
            return ((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z')) || ((c >= '0') && (c <= '9'));
        }
    
        /**
         * @brief remove all "/0x00" parts
         *
         * @param src
         * @return modified string
         */
        std::string remove0x00(const std::string& src) const
        {
            return std::regex_replace(src, std::regex("/0x00"), "");
        }
    
        /**
         * @brief replace all non ID char with '_' (one '_' may replace several non ID char)
         *
         * @param src
         * @return modified string
         */
        std::string str2ID(const std::string& src) const
        {
            std::string dst;
            bool need_underscore = false;
            for (char c : src) {
                if (isIDChar(c) || (c == '/')) {
                    if (need_underscore) {
                        dst.push_back('_');
                        need_underscore = false;
                    }
                    dst.push_back(c);
                } else {
                    need_underscore = true;
                }
            }
            return dst;
        }
    
        /**
         * @brief Keep only the last n slash-parts
         *
         * @param src
         * @param n : 1 indicates the last slash-part
         * @return modified string
         */
        std::string cut(const std::string& src, int n) const
        {
            std::string rdst;
            for (int i = int(src.length())-1; i >= 0; i--) {
                char c = src[i];
                if (c != '/') {
                    rdst.push_back(c);
                } else if (n == 1) {
                    std::string dst;
                    for (int j = int(rdst.length())-1; j >= 0; j--) {
                        dst.push_back(rdst[j]);
                    }
                    return dst;
                } else {
                    n--;
                    rdst.push_back(c);
                }
            }
            return src;
        }
    
        void addFullPath(const std::string& label) { fFullPaths.push_back(buildPath(label)); }
    
        /**
         * @brief Compute the mapping between full path and short names
         */
        void computeShortNames()
        {
            std::vector<std::string>           uniquePaths;  // all full paths transformed but made unique with a prefix
            std::map<std::string, std::string> unique2full;  // all full paths transformed but made unique with a prefix
            char num_buffer[16];
            int pnum = 0;
        
            for (const auto& s : fFullPaths) {
                sprintf(num_buffer, "%d", pnum++);
                std::string u = "/P" + std::string(num_buffer) + str2ID(remove0x00(s));
                uniquePaths.push_back(u);
                unique2full[u] = s;  // remember the full path associated to a unique path
            }
        
            std::map<std::string, int> uniquePath2level;                // map path to level
            for (const auto& s : uniquePaths) uniquePath2level[s] = 1;   // we init all levels to 1
            bool have_collisions = true;
        
            while (have_collisions) {
                // compute collision list
                std::set<std::string>              collisionSet;
                std::map<std::string, std::string> short2full;
                have_collisions = false;
                for (const auto& it : uniquePath2level) {
                    std::string u = it.first;
                    int n = it.second;
                    std::string shortName = cut(u, n);
                    auto p = short2full.find(shortName);
                    if (p == short2full.end()) {
                        // no collision
                        short2full[shortName] = u;
                    } else {
                        // we have a collision, add the two paths to the collision set
                        have_collisions = true;
                        collisionSet.insert(u);
                        collisionSet.insert(p->second);
                    }
                }
                for (const auto& s : collisionSet) uniquePath2level[s]++;  // increase level of colliding path
            }
        
            for (const auto& it : uniquePath2level) {
                std::string u = it.first;
                int n = it.second;
                std::string shortName = replaceCharList(cut(u, n), {'/'}, '_');
                fFull2Short[unique2full[u]] = shortName;
            }
        }
    
        std::string replaceCharList(const std::string& str, const std::vector<char>& ch1, char ch2)
        {
            auto beg = ch1.begin();
            auto end = ch1.end();
            std::string res = str;
            for (size_t i = 0; i < str.length(); ++i) {
                if (std::find(beg, end, str[i]) != end) res[i] = ch2;
            }
            return res;
        }
     
    public:
    
        PathBuilder() {}
        virtual ~PathBuilder() {}
    
        // Return true for the first level of groups
        bool pushLabel(const std::string& label) { fControlsLevel.push_back(label); return fControlsLevel.size() == 1;}
    
        // Return true for the last level of groups
        bool popLabel() { fControlsLevel.pop_back(); return fControlsLevel.size() == 0; }
    
        std::string buildPath(const std::string& label)
        {
            std::string res = "/";
            for (size_t i = 0; i < fControlsLevel.size(); i++) {
                res = res + fControlsLevel[i] + "/";
            }
            res += label;
            return replaceCharList(res, {' ', '#', '*', ',', '?', '[', ']', '{', '}', '(', ')'}, '_');
        }
    
};

#endif  // __PathBuilder__
/**************************  END  PathBuilder.h **************************/

/*******************************************************************************
 * MapUI : Faust User Interface.
 *
 * This class creates:
 * - a map of 'labels' and zones for each UI item.
 * - a map of unique 'shortname' (built so that they never collide) and zones
 * - a map of complete hierarchical 'paths' and zones for each UI item
 *
 * Simple 'labels', 'shortname' and complete 'paths' (to fully discriminate between possible same
 * 'labels' at different location in the UI hierachy) can be used to access a given parameter.
 ******************************************************************************/

class FAUST_API MapUI : public UI, public PathBuilder
{
    
    protected:
    
        // Label zone map
        std::map<std::string, FAUSTFLOAT*> fLabelZoneMap;
    
        // Shortname zone map
        std::map<std::string, FAUSTFLOAT*> fShortnameZoneMap;
    
        // Full path map
        std::map<std::string, FAUSTFLOAT*> fPathZoneMap;
    
        void addZoneLabel(const std::string& label, FAUSTFLOAT* zone)
        {
            std::string path = buildPath(label);
            fFullPaths.push_back(path);
            fPathZoneMap[path] = zone;
            fLabelZoneMap[label] = zone;
        }
    
    public:
        
        MapUI() {}
        virtual ~MapUI() {}
        
        // -- widget's layouts
        void openTabBox(const char* label)
        {
            pushLabel(label);
        }
        void openHorizontalBox(const char* label)
        {
            pushLabel(label);
        }
        void openVerticalBox(const char* label)
        {
            pushLabel(label);
        }
        void closeBox()
        {
            if (popLabel()) {
                // Shortnames can be computed when all fullnames are known
                computeShortNames();
                // Fill 'shortname' map
                for (const auto& it : fFullPaths) {
                    fShortnameZoneMap[fFull2Short[it]] = fPathZoneMap[it];
                }
            }
        }
        
        // -- active widgets
        void addButton(const char* label, FAUSTFLOAT* zone)
        {
            addZoneLabel(label, zone);
        }
        void addCheckButton(const char* label, FAUSTFLOAT* zone)
        {
            addZoneLabel(label, zone);
        }
        void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
        {
            addZoneLabel(label, zone);
        }
        void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
        {
            addZoneLabel(label, zone);
        }
        void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
        {
            addZoneLabel(label, zone);
        }
        
        // -- passive widgets
        void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT fmin, FAUSTFLOAT fmax)
        {
            addZoneLabel(label, zone);
        }
        void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT fmin, FAUSTFLOAT fmax)
        {
            addZoneLabel(label, zone);
        }
    
        // -- soundfiles
        virtual void addSoundfile(const char* label, const char* filename, Soundfile** sf_zone) {}
        
        // -- metadata declarations
        virtual void declare(FAUSTFLOAT* zone, const char* key, const char* val)
        {}
        
        // setParamValue/getParamValue
        void setParamValue(const std::string& path, FAUSTFLOAT value)
        {
            if (fPathZoneMap.find(path) != fPathZoneMap.end()) {
                *fPathZoneMap[path] = value;
            } else if (fShortnameZoneMap.find(path) != fShortnameZoneMap.end()) {
                *fShortnameZoneMap[path] = value;
            } else if (fLabelZoneMap.find(path) != fLabelZoneMap.end()) {
                *fLabelZoneMap[path] = value;
            } else {
                fprintf(stderr, "ERROR : setParamValue '%s' not found\n", path.c_str());
            }
        }
        
        FAUSTFLOAT getParamValue(const std::string& path)
        {
            if (fPathZoneMap.find(path) != fPathZoneMap.end()) {
                return *fPathZoneMap[path];
            } else if (fShortnameZoneMap.find(path) != fShortnameZoneMap.end()) {
                return *fShortnameZoneMap[path];
            } else if (fLabelZoneMap.find(path) != fLabelZoneMap.end()) {
                return *fLabelZoneMap[path];
            } else {
                fprintf(stderr, "ERROR : getParamValue '%s' not found\n", path.c_str());
                return 0;
            }
        }
    
        // map access 
        std::map<std::string, FAUSTFLOAT*>& getFullpathMap() { return fPathZoneMap; }
        std::map<std::string, FAUSTFLOAT*>& getShortnameMap() { return fShortnameZoneMap; }
        std::map<std::string, FAUSTFLOAT*>& getLabelMap() { return fLabelZoneMap; }
        
        int getParamsCount() { return int(fPathZoneMap.size()); }
        
        std::string getParamAddress(int index)
        {
            if (index < 0 || index > int(fPathZoneMap.size())) {
                return "";
            } else {
                auto it = fPathZoneMap.begin();
                while (index-- > 0 && it++ != fPathZoneMap.end()) {}
                return it->first;
            }
        }
        
        const char* getParamAddress1(int index)
        {
            if (index < 0 || index > int(fPathZoneMap.size())) {
                return nullptr;
            } else {
                auto it = fPathZoneMap.begin();
                while (index-- > 0 && it++ != fPathZoneMap.end()) {}
                return it->first.c_str();
            }
        }
    
        std::string getParamShortname(int index)
        {
            if (index < 0 || index > int(fShortnameZoneMap.size())) {
                return "";
            } else {
                auto it = fShortnameZoneMap.begin();
                while (index-- > 0 && it++ != fShortnameZoneMap.end()) {}
                return it->first;
            }
        }
        
        const char* getParamShortname1(int index)
        {
            if (index < 0 || index > int(fShortnameZoneMap.size())) {
                return nullptr;
            } else {
                auto it = fShortnameZoneMap.begin();
                while (index-- > 0 && it++ != fShortnameZoneMap.end()) {}
                return it->first.c_str();
            }
        }
    
        std::string getParamLabel(int index)
        {
            if (index < 0 || index > int(fLabelZoneMap.size())) {
                return "";
            } else {
                auto it = fLabelZoneMap.begin();
                while (index-- > 0 && it++ != fLabelZoneMap.end()) {}
                return it->first;
            }
        }
        
        const char* getParamLabel1(int index)
        {
            if (index < 0 || index > int(fLabelZoneMap.size())) {
                return nullptr;
            } else {
                auto it = fLabelZoneMap.begin();
                while (index-- > 0 && it++ != fLabelZoneMap.end()) {}
                return it->first.c_str();
            }
        }
    
        std::string getParamAddress(FAUSTFLOAT* zone)
        {
            for (const auto& it : fPathZoneMap) {
                if (it.second == zone) return it.first;
            }
            return "";
        }
    
        FAUSTFLOAT* getParamZone(const std::string& str)
        {
            if (fPathZoneMap.find(str) != fPathZoneMap.end()) {
                return fPathZoneMap[str];
            } else if (fShortnameZoneMap.find(str) != fShortnameZoneMap.end()) {
                return fShortnameZoneMap[str];
            } else if (fLabelZoneMap.find(str) != fLabelZoneMap.end()) {
                return fLabelZoneMap[str];
            }
            return nullptr;
        }
    
        FAUSTFLOAT* getParamZone(int index)
        {
            if (index < 0 || index > int(fPathZoneMap.size())) {
                return nullptr;
            } else {
                auto it = fPathZoneMap.begin();
                while (index-- > 0 && it++ != fPathZoneMap.end()) {}
                return it->second;
            }
        }
    
        static bool endsWith(const std::string& str, const std::string& end)
        {
            size_t l1 = str.length();
            size_t l2 = end.length();
            return (l1 >= l2) && (0 == str.compare(l1 - l2, l2, end));
        }
    
};

#endif // FAUST_MAPUI_H
/**************************  END  MapUI.h **************************/
/************************** BEGIN meta.h *******************************
 FAUST Architecture File
 Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __meta__
#define __meta__


/**
 The base class of Meta handler to be used in dsp::metadata(Meta* m) method to retrieve (key, value) metadata.
 */
struct FAUST_API Meta {
    virtual ~Meta() {}
    virtual void declare(const char* key, const char* value) = 0;
};

#endif
/**************************  END  meta.h **************************/
/************************** BEGIN dsp.h ********************************
 FAUST Architecture File
 Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __dsp__
#define __dsp__

#include <string>
#include <vector>


#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

struct FAUST_API UI;
struct FAUST_API Meta;

/**
 * DSP memory manager.
 */

struct FAUST_API dsp_memory_manager {
    
    virtual ~dsp_memory_manager() {}
    
    /**
     * Inform the Memory Manager with the number of expected memory zones.
     * @param count - the number of expected memory zones
     */
    virtual void begin(size_t count) {}
    
    /**
     * Give the Memory Manager information on a given memory zone.
     * @param size - the size in bytes of the memory zone
     * @param reads - the number of Read access to the zone used to compute one frame
     * @param writes - the number of Write access to the zone used to compute one frame
     */
    virtual void info(size_t size, size_t reads, size_t writes) {}
    
    /**
     * Inform the Memory Manager that all memory zones have been described,
     * to possibly start a 'compute the best allocation strategy' step.
     */
    virtual void end() {}
    
    /**
     * Allocate a memory zone.
     * @param size - the memory zone size in bytes
     */
    virtual void* allocate(size_t size) = 0;
    
    /**
     * Destroy a memory zone.
     * @param ptr - the memory zone pointer to be deallocated
     */
    virtual void destroy(void* ptr) = 0;
    
};

/**
* Signal processor definition.
*/

class FAUST_API dsp {

    public:

        dsp() {}
        virtual ~dsp() {}

        /* Return instance number of audio inputs */
        virtual int getNumInputs() = 0;
    
        /* Return instance number of audio outputs */
        virtual int getNumOutputs() = 0;
    
        /**
         * Trigger the ui_interface parameter with instance specific calls
         * to 'openTabBox', 'addButton', 'addVerticalSlider'... in order to build the UI.
         *
         * @param ui_interface - the user interface builder
         */
        virtual void buildUserInterface(UI* ui_interface) = 0;
    
        /* Return the sample rate currently used by the instance */
        virtual int getSampleRate() = 0;
    
        /**
         * Global init, calls the following methods:
         * - static class 'classInit': static tables initialization
         * - 'instanceInit': constants and instance state initialization
         *
         * @param sample_rate - the sampling rate in Hz
         */
        virtual void init(int sample_rate) = 0;

        /**
         * Init instance state
         *
         * @param sample_rate - the sampling rate in Hz
         */
        virtual void instanceInit(int sample_rate) = 0;
    
        /**
         * Init instance constant state
         *
         * @param sample_rate - the sampling rate in Hz
         */
        virtual void instanceConstants(int sample_rate) = 0;
    
        /* Init default control parameters values */
        virtual void instanceResetUserInterface() = 0;
    
        /* Init instance state (like delay lines...) but keep the control parameter values */
        virtual void instanceClear() = 0;
 
        /**
         * Return a clone of the instance.
         *
         * @return a copy of the instance on success, otherwise a null pointer.
         */
        virtual dsp* clone() = 0;
    
        /**
         * Trigger the Meta* parameter with instance specific calls to 'declare' (key, value) metadata.
         *
         * @param m - the Meta* meta user
         */
        virtual void metadata(Meta* m) = 0;
    
        /**
         * DSP instance computation, to be called with successive in/out audio buffers.
         *
         * @param count - the number of frames to compute
         * @param inputs - the input audio buffers as an array of non-interleaved FAUSTFLOAT samples (eiher float, double or quad)
         * @param outputs - the output audio buffers as an array of non-interleaved FAUSTFLOAT samples (eiher float, double or quad)
         *
         */
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) = 0;
    
        /**
         * DSP instance computation: alternative method to be used by subclasses.
         *
         * @param date_usec - the timestamp in microsec given by audio driver.
         * @param count - the number of frames to compute
         * @param inputs - the input audio buffers as an array of non-interleaved FAUSTFLOAT samples (either float, double or quad)
         * @param outputs - the output audio buffers as an array of non-interleaved FAUSTFLOAT samples (either float, double or quad)
         *
         */
        virtual void compute(double /*date_usec*/, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { compute(count, inputs, outputs); }
       
};

/**
 * Generic DSP decorator.
 */

class FAUST_API decorator_dsp : public dsp {

    protected:

        dsp* fDSP;

    public:

        decorator_dsp(dsp* dsp = nullptr):fDSP(dsp) {}
        virtual ~decorator_dsp() { delete fDSP; }

        virtual int getNumInputs() { return fDSP->getNumInputs(); }
        virtual int getNumOutputs() { return fDSP->getNumOutputs(); }
        virtual void buildUserInterface(UI* ui_interface) { fDSP->buildUserInterface(ui_interface); }
        virtual int getSampleRate() { return fDSP->getSampleRate(); }
        virtual void init(int sample_rate) { fDSP->init(sample_rate); }
        virtual void instanceInit(int sample_rate) { fDSP->instanceInit(sample_rate); }
        virtual void instanceConstants(int sample_rate) { fDSP->instanceConstants(sample_rate); }
        virtual void instanceResetUserInterface() { fDSP->instanceResetUserInterface(); }
        virtual void instanceClear() { fDSP->instanceClear(); }
        virtual decorator_dsp* clone() { return new decorator_dsp(fDSP->clone()); }
        virtual void metadata(Meta* m) { fDSP->metadata(m); }
        // Beware: subclasses usually have to overload the two 'compute' methods
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { fDSP->compute(count, inputs, outputs); }
        virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { fDSP->compute(date_usec, count, inputs, outputs); }
    
};

/**
 * DSP factory class, used with LLVM and Interpreter backends
 * to create DSP instances from a compiled DSP program.
 */

class FAUST_API dsp_factory {
    
    protected:
    
        // So that to force sub-classes to use deleteDSPFactory(dsp_factory* factory);
        virtual ~dsp_factory() {}
    
    public:
    
        virtual std::string getName() = 0;
        virtual std::string getSHAKey() = 0;
        virtual std::string getDSPCode() = 0;
        virtual std::string getCompileOptions() = 0;
        virtual std::vector<std::string> getLibraryList() = 0;
        virtual std::vector<std::string> getIncludePathnames() = 0;
    
        virtual dsp* createDSPInstance() = 0;
    
        virtual void setMemoryManager(dsp_memory_manager* manager) = 0;
        virtual dsp_memory_manager* getMemoryManager() = 0;
    
};

// Denormal handling

#if defined (__SSE__)
#include <xmmintrin.h>
#endif

class FAUST_API ScopedNoDenormals {
    
    private:
    
        intptr_t fpsr;
        
        void setFpStatusRegister(intptr_t fpsr_aux) noexcept
        {
        #if defined (__arm64__) || defined (__aarch64__)
           asm volatile("msr fpcr, %0" : : "ri" (fpsr_aux));
        #elif defined (__SSE__)
            _mm_setcsr(static_cast<uint32_t>(fpsr_aux));
        #endif
        }
        
        void getFpStatusRegister() noexcept
        {
        #if defined (__arm64__) || defined (__aarch64__)
            asm volatile("mrs %0, fpcr" : "=r" (fpsr));
        #elif defined ( __SSE__)
            fpsr = static_cast<intptr_t>(_mm_getcsr());
        #endif
        }
    
    public:
    
        ScopedNoDenormals() noexcept
        {
        #if defined (__arm64__) || defined (__aarch64__)
            intptr_t mask = (1 << 24 /* FZ */);
        #else
            #if defined(__SSE__)
            #if defined(__SSE2__)
                intptr_t mask = 0x8040;
            #else
                intptr_t mask = 0x8000;
            #endif
            #else
                intptr_t mask = 0x0000;
            #endif
        #endif
            getFpStatusRegister();
            setFpStatusRegister(fpsr | mask);
        }
        
        ~ScopedNoDenormals() noexcept
        {
            setFpStatusRegister(fpsr);
        }

};

#define AVOIDDENORMALS ScopedNoDenormals();

#endif

/************************** END dsp.h **************************/

// BEGIN-FAUSTDSP


#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

/* link with : "" */
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

#ifndef FAUSTCLASS 
#define FAUSTCLASS Delay
#endif

#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

#if defined(_WIN32)
#define RESTRICT __restrict
#else
#define RESTRICT __restrict__
#endif


class Delay : public dsp {
	
 private:
	
	FAUSTFLOAT fVslider0;
	int fSampleRate;
	double fConst2;
	double fConst3;
	FAUSTFLOAT fVslider1;
	double fConst4;
	double fRec1[2];
	double fConst5;
	FAUSTFLOAT fVslider2;
	double fRec5[2];
	double fConst6;
	double fConst7;
	FAUSTFLOAT fVslider3;
	double fRec6[2];
	double fRec4[2];
	int IOTA0;
	double fVec0[524288];
	double fConst8;
	FAUSTFLOAT fVslider4;
	double fRec11[2];
	double fConst9;
	double fConst10;
	double fRec7[2];
	double fRec8[2];
	double fRec9[2];
	double fRec10[2];
	FAUSTFLOAT fVslider5;
	double fRec12[2];
	double fVec1[2];
	double fConst11;
	FAUSTFLOAT fVslider6;
	double fRec15[2];
	double fRec14[2];
	double fVec2[524288];
	FAUSTFLOAT fVslider7;
	double fRec20[2];
	double fRec16[2];
	double fRec17[2];
	double fRec18[2];
	double fRec19[2];
	double fRec2[2];
	FAUSTFLOAT fVslider8;
	double fRec21[2];
	double fVec3[2];
	double fConst12;
	double fRec0[2];
	FAUSTFLOAT fVslider9;
	double fRec26[2];
	FAUSTFLOAT fVslider10;
	double fRec27[2];
	double fRec25[2];
	double fVec4[524288];
	FAUSTFLOAT fVslider11;
	double fRec32[2];
	double fRec28[2];
	double fRec29[2];
	double fRec30[2];
	double fRec31[2];
	double fVec5[2];
	FAUSTFLOAT fVslider12;
	double fRec35[2];
	double fRec34[2];
	double fVec6[524288];
	FAUSTFLOAT fVslider13;
	double fRec40[2];
	double fRec36[2];
	double fRec37[2];
	double fRec38[2];
	double fRec39[2];
	double fRec23[2];
	FAUSTFLOAT fVslider14;
	double fRec41[2];
	double fVec7[2];
	double fRec22[2];
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("aanl.lib/ADAA1:author", "Dario Sanfilippo");
		m->declare("aanl.lib/ADAA1:copyright", "Copyright (C) 2021 Dario Sanfilippo     <sanfilippo.dario@gmail.com>");
		m->declare("aanl.lib/ADAA1:license", "LGPL v3.0 license");
		m->declare("aanl.lib/name", "Faust Antialiased Nonlinearities");
		m->declare("aanl.lib/tanh1:author", "Dario Sanfilippo");
		m->declare("aanl.lib/tanh1:copyright", "Copyright (C) 2021 Dario Sanfilippo     <sanfilippo.dario@gmail.com>");
		m->declare("aanl.lib/tanh1:license", "LGPL v3.0 license");
		m->declare("aanl.lib/version", "0.3");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.8");
		m->declare("compile_options", "-a faustMinimal.h -lang cpp -i -cn Delay -es 1 -mcd 16 -double -ftz 0");
		m->declare("delays.lib/name", "Faust Delay Library");
		m->declare("delays.lib/version", "0.1");
		m->declare("filename", "delay.dsp");
		m->declare("filters.lib/dcblockerat:author", "Julius O. Smith III");
		m->declare("filters.lib/dcblockerat:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/dcblockerat:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/lowpass0_highpass1", "MIT-style STK-4.3 license");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/pole:author", "Julius O. Smith III");
		m->declare("filters.lib/pole:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/pole:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/version", "0.3");
		m->declare("filters.lib/zero:author", "Julius O. Smith III");
		m->declare("filters.lib/zero:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/zero:license", "MIT-style STK-4.3 license");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.5");
		m->declare("name", "delay");
		m->declare("platform.lib/name", "Generic Platform Library");
		m->declare("platform.lib/version", "0.2");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "0.3");
		m->declare("vaeffects.lib/name", "Faust Virtual Analog Filter Effect Library");
		m->declare("vaeffects.lib/sallenKeyOnePole:author", "Eric Tarr");
		m->declare("vaeffects.lib/sallenKeyOnePole:license", "MIT-style STK-4.3 license");
		m->declare("vaeffects.lib/sallenKeyOnePoleHPF:author", "Eric Tarr");
		m->declare("vaeffects.lib/sallenKeyOnePoleHPF:license", "MIT-style STK-4.3 license");
		m->declare("vaeffects.lib/sallenKeyOnePoleLPF:author", "Eric Tarr");
		m->declare("vaeffects.lib/sallenKeyOnePoleLPF:license", "MIT-style STK-4.3 license");
		m->declare("vaeffects.lib/version", "0.2");
	}

	virtual int getNumInputs() {
		return 2;
	}
	virtual int getNumOutputs() {
		return 2;
	}
	
	static void classInit(int sample_rate) {
	}
	
	virtual void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		double fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSampleRate)));
		double fConst1 = 62.831853071795862 / fConst0;
		fConst2 = 1.0 / (fConst1 + 1.0);
		fConst3 = 44.100000000000001 / fConst0;
		fConst4 = 1.0 - fConst3;
		fConst5 = 0.441 / fConst0;
		fConst6 = 6.2831853071795862 / fConst0;
		fConst7 = 0.0022050000000000004 / fConst0;
		fConst8 = 1.5 * fConst0;
		fConst9 = 23.809523809523807 / fConst0;
		fConst10 = 0.0 - fConst9;
		fConst11 = 1.0 / fConst0;
		fConst12 = 1.0 - fConst1;
	}
	
	virtual void instanceResetUserInterface() {
		fVslider0 = FAUSTFLOAT(100.0);
		fVslider1 = FAUSTFLOAT(0.0);
		fVslider2 = FAUSTFLOAT(0.0);
		fVslider3 = FAUSTFLOAT(20000.0);
		fVslider4 = FAUSTFLOAT(0.0);
		fVslider5 = FAUSTFLOAT(0.0);
		fVslider6 = FAUSTFLOAT(20.0);
		fVslider7 = FAUSTFLOAT(0.0);
		fVslider8 = FAUSTFLOAT(0.0);
		fVslider9 = FAUSTFLOAT(0.0);
		fVslider10 = FAUSTFLOAT(20000.0);
		fVslider11 = FAUSTFLOAT(0.0);
		fVslider12 = FAUSTFLOAT(20.0);
		fVslider13 = FAUSTFLOAT(0.0);
		fVslider14 = FAUSTFLOAT(0.0);
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			fRec1[l0] = 0.0;
		}
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			fRec5[l1] = 0.0;
		}
		for (int l2 = 0; l2 < 2; l2 = l2 + 1) {
			fRec6[l2] = 0.0;
		}
		for (int l3 = 0; l3 < 2; l3 = l3 + 1) {
			fRec4[l3] = 0.0;
		}
		IOTA0 = 0;
		for (int l4 = 0; l4 < 524288; l4 = l4 + 1) {
			fVec0[l4] = 0.0;
		}
		for (int l5 = 0; l5 < 2; l5 = l5 + 1) {
			fRec11[l5] = 0.0;
		}
		for (int l6 = 0; l6 < 2; l6 = l6 + 1) {
			fRec7[l6] = 0.0;
		}
		for (int l7 = 0; l7 < 2; l7 = l7 + 1) {
			fRec8[l7] = 0.0;
		}
		for (int l8 = 0; l8 < 2; l8 = l8 + 1) {
			fRec9[l8] = 0.0;
		}
		for (int l9 = 0; l9 < 2; l9 = l9 + 1) {
			fRec10[l9] = 0.0;
		}
		for (int l10 = 0; l10 < 2; l10 = l10 + 1) {
			fRec12[l10] = 0.0;
		}
		for (int l11 = 0; l11 < 2; l11 = l11 + 1) {
			fVec1[l11] = 0.0;
		}
		for (int l12 = 0; l12 < 2; l12 = l12 + 1) {
			fRec15[l12] = 0.0;
		}
		for (int l13 = 0; l13 < 2; l13 = l13 + 1) {
			fRec14[l13] = 0.0;
		}
		for (int l14 = 0; l14 < 524288; l14 = l14 + 1) {
			fVec2[l14] = 0.0;
		}
		for (int l15 = 0; l15 < 2; l15 = l15 + 1) {
			fRec20[l15] = 0.0;
		}
		for (int l16 = 0; l16 < 2; l16 = l16 + 1) {
			fRec16[l16] = 0.0;
		}
		for (int l17 = 0; l17 < 2; l17 = l17 + 1) {
			fRec17[l17] = 0.0;
		}
		for (int l18 = 0; l18 < 2; l18 = l18 + 1) {
			fRec18[l18] = 0.0;
		}
		for (int l19 = 0; l19 < 2; l19 = l19 + 1) {
			fRec19[l19] = 0.0;
		}
		for (int l20 = 0; l20 < 2; l20 = l20 + 1) {
			fRec2[l20] = 0.0;
		}
		for (int l21 = 0; l21 < 2; l21 = l21 + 1) {
			fRec21[l21] = 0.0;
		}
		for (int l22 = 0; l22 < 2; l22 = l22 + 1) {
			fVec3[l22] = 0.0;
		}
		for (int l23 = 0; l23 < 2; l23 = l23 + 1) {
			fRec0[l23] = 0.0;
		}
		for (int l24 = 0; l24 < 2; l24 = l24 + 1) {
			fRec26[l24] = 0.0;
		}
		for (int l25 = 0; l25 < 2; l25 = l25 + 1) {
			fRec27[l25] = 0.0;
		}
		for (int l26 = 0; l26 < 2; l26 = l26 + 1) {
			fRec25[l26] = 0.0;
		}
		for (int l27 = 0; l27 < 524288; l27 = l27 + 1) {
			fVec4[l27] = 0.0;
		}
		for (int l28 = 0; l28 < 2; l28 = l28 + 1) {
			fRec32[l28] = 0.0;
		}
		for (int l29 = 0; l29 < 2; l29 = l29 + 1) {
			fRec28[l29] = 0.0;
		}
		for (int l30 = 0; l30 < 2; l30 = l30 + 1) {
			fRec29[l30] = 0.0;
		}
		for (int l31 = 0; l31 < 2; l31 = l31 + 1) {
			fRec30[l31] = 0.0;
		}
		for (int l32 = 0; l32 < 2; l32 = l32 + 1) {
			fRec31[l32] = 0.0;
		}
		for (int l33 = 0; l33 < 2; l33 = l33 + 1) {
			fVec5[l33] = 0.0;
		}
		for (int l34 = 0; l34 < 2; l34 = l34 + 1) {
			fRec35[l34] = 0.0;
		}
		for (int l35 = 0; l35 < 2; l35 = l35 + 1) {
			fRec34[l35] = 0.0;
		}
		for (int l36 = 0; l36 < 524288; l36 = l36 + 1) {
			fVec6[l36] = 0.0;
		}
		for (int l37 = 0; l37 < 2; l37 = l37 + 1) {
			fRec40[l37] = 0.0;
		}
		for (int l38 = 0; l38 < 2; l38 = l38 + 1) {
			fRec36[l38] = 0.0;
		}
		for (int l39 = 0; l39 < 2; l39 = l39 + 1) {
			fRec37[l39] = 0.0;
		}
		for (int l40 = 0; l40 < 2; l40 = l40 + 1) {
			fRec38[l40] = 0.0;
		}
		for (int l41 = 0; l41 < 2; l41 = l41 + 1) {
			fRec39[l41] = 0.0;
		}
		for (int l42 = 0; l42 < 2; l42 = l42 + 1) {
			fRec23[l42] = 0.0;
		}
		for (int l43 = 0; l43 < 2; l43 = l43 + 1) {
			fRec41[l43] = 0.0;
		}
		for (int l44 = 0; l44 < 2; l44 = l44 + 1) {
			fVec7[l44] = 0.0;
		}
		for (int l45 = 0; l45 < 2; l45 = l45 + 1) {
			fRec22[l45] = 0.0;
		}
	}
	
	virtual void init(int sample_rate) {
		classInit(sample_rate);
		instanceInit(sample_rate);
	}
	virtual void instanceInit(int sample_rate) {
		instanceConstants(sample_rate);
		instanceResetUserInterface();
		instanceClear();
	}
	
	virtual Delay* clone() {
		return new Delay();
	}
	
	virtual int getSampleRate() {
		return fSampleRate;
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("delay");
		ui_interface->declare(&fVslider6, "scale", "log");
		ui_interface->declare(&fVslider6, "style", "knob");
		ui_interface->declare(&fVslider6, "unit", "Hz");
		ui_interface->addVerticalSlider("cutoffHP_L", &fVslider6, FAUSTFLOAT(20.0), FAUSTFLOAT(20.0), FAUSTFLOAT(20000.0), FAUSTFLOAT(0.10000000000000001));
		ui_interface->declare(&fVslider12, "scale", "log");
		ui_interface->declare(&fVslider12, "style", "knob");
		ui_interface->declare(&fVslider12, "unit", "Hz");
		ui_interface->addVerticalSlider("cutoffHP_R", &fVslider12, FAUSTFLOAT(20.0), FAUSTFLOAT(20.0), FAUSTFLOAT(20000.0), FAUSTFLOAT(0.10000000000000001));
		ui_interface->declare(&fVslider3, "scale", "log");
		ui_interface->declare(&fVslider3, "style", "knob");
		ui_interface->declare(&fVslider3, "unit", "Hz");
		ui_interface->addVerticalSlider("cutoffLP_L", &fVslider3, FAUSTFLOAT(20000.0), FAUSTFLOAT(20.0), FAUSTFLOAT(20000.0), FAUSTFLOAT(0.10000000000000001));
		ui_interface->declare(&fVslider10, "scale", "log");
		ui_interface->declare(&fVslider10, "style", "knob");
		ui_interface->declare(&fVslider10, "unit", "Hz");
		ui_interface->addVerticalSlider("cutoffLP_R", &fVslider10, FAUSTFLOAT(20000.0), FAUSTFLOAT(20.0), FAUSTFLOAT(20000.0), FAUSTFLOAT(0.10000000000000001));
		ui_interface->declare(&fVslider7, "scale", "log");
		ui_interface->declare(&fVslider7, "style", "knob");
		ui_interface->declare(&fVslider7, "unit", "ms");
		ui_interface->addVerticalSlider("delayTime_L", &fVslider7, FAUSTFLOAT(0.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1500.0), FAUSTFLOAT(0.01));
		ui_interface->declare(&fVslider13, "scale", "log");
		ui_interface->declare(&fVslider13, "style", "knob");
		ui_interface->declare(&fVslider13, "unit", "ms");
		ui_interface->addVerticalSlider("delayTime_R", &fVslider13, FAUSTFLOAT(0.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1500.0), FAUSTFLOAT(0.01));
		ui_interface->declare(&fVslider5, "style", "knob");
		ui_interface->declare(&fVslider5, "unit", "dB");
		ui_interface->addVerticalSlider("drive", &fVslider5, FAUSTFLOAT(0.0), FAUSTFLOAT(-24.0), FAUSTFLOAT(12.0), FAUSTFLOAT(0.10000000000000001));
		ui_interface->declare(&fVslider8, "style", "knob");
		ui_interface->declare(&fVslider8, "unit", "%");
		ui_interface->addVerticalSlider("dryWet_L", &fVslider8, FAUSTFLOAT(0.0), FAUSTFLOAT(0.0), FAUSTFLOAT(100.0), FAUSTFLOAT(0.0));
		ui_interface->declare(&fVslider14, "style", "knob");
		ui_interface->declare(&fVslider14, "unit", "%");
		ui_interface->addVerticalSlider("dryWet_R", &fVslider14, FAUSTFLOAT(0.0), FAUSTFLOAT(0.0), FAUSTFLOAT(100.0), FAUSTFLOAT(0.0));
		ui_interface->declare(&fVslider2, "style", "knob");
		ui_interface->declare(&fVslider2, "unit", "%");
		ui_interface->addVerticalSlider("feedback_L", &fVslider2, FAUSTFLOAT(0.0), FAUSTFLOAT(0.0), FAUSTFLOAT(100.0), FAUSTFLOAT(0.10000000000000001));
		ui_interface->declare(&fVslider9, "style", "knob");
		ui_interface->declare(&fVslider9, "unit", "%");
		ui_interface->addVerticalSlider("feedback_R", &fVslider9, FAUSTFLOAT(0.0), FAUSTFLOAT(0.0), FAUSTFLOAT(100.0), FAUSTFLOAT(0.10000000000000001));
		ui_interface->declare(&fVslider4, "scale", "log");
		ui_interface->declare(&fVslider4, "style", "knob");
		ui_interface->declare(&fVslider4, "unit", "ms");
		ui_interface->addVerticalSlider("preDelay_L", &fVslider4, FAUSTFLOAT(0.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1500.0), FAUSTFLOAT(0.01));
		ui_interface->declare(&fVslider11, "scale", "log");
		ui_interface->declare(&fVslider11, "style", "knob");
		ui_interface->declare(&fVslider11, "unit", "ms");
		ui_interface->addVerticalSlider("preDelay_R", &fVslider11, FAUSTFLOAT(0.0), FAUSTFLOAT(0.0), FAUSTFLOAT(1500.0), FAUSTFLOAT(0.01));
		ui_interface->declare(&fVslider0, "style", "knob");
		ui_interface->declare(&fVslider0, "unit", "%");
		ui_interface->addVerticalSlider("stereoWidth", &fVslider0, FAUSTFLOAT(100.0), FAUSTFLOAT(0.0), FAUSTFLOAT(100.0), FAUSTFLOAT(1.0));
		ui_interface->declare(&fVslider1, "style", "knob");
		ui_interface->declare(&fVslider1, "unit", "dB");
		ui_interface->addVerticalSlider("volume", &fVslider1, FAUSTFLOAT(0.0), FAUSTFLOAT(-24.0), FAUSTFLOAT(12.0), FAUSTFLOAT(0.10000000000000001));
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		double fSlow0 = 0.01 * double(fVslider0);
		double fSlow1 = fConst3 * std::pow(10.0, 0.050000000000000003 * double(fVslider1));
		double fSlow2 = fConst5 * double(fVslider2);
		double fSlow3 = fConst7 * double(fVslider3);
		double fSlow4 = 0.0441 * double(fVslider4);
		double fSlow5 = fConst3 * std::pow(10.0, 0.050000000000000003 * double(fVslider5));
		double fSlow6 = fConst7 * double(fVslider6);
		double fSlow7 = 0.0441 * double(fVslider7);
		double fSlow8 = fConst5 * double(fVslider8);
		double fSlow9 = 0.5 * (1.0 - fSlow0);
		double fSlow10 = fConst5 * double(fVslider9);
		double fSlow11 = fConst7 * double(fVslider10);
		double fSlow12 = 0.0441 * double(fVslider11);
		double fSlow13 = fConst7 * double(fVslider12);
		double fSlow14 = 0.0441 * double(fVslider13);
		double fSlow15 = fConst5 * double(fVslider14);
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			fRec1[0] = fSlow1 + fConst4 * fRec1[1];
			fRec5[0] = fSlow2 + fConst4 * fRec5[1];
			fRec6[0] = fSlow3 + fConst4 * fRec6[1];
			double fTemp0 = std::tan(fConst6 * std::pow(10.0, 3.0 * fRec6[0] + 1.0));
			double fTemp1 = ((fRec5[0] * fRec2[1] - fRec4[1]) * fTemp0) / (fTemp0 + 1.0);
			double fRec3 = fRec4[1] + fTemp1;
			fRec4[0] = fRec4[1] + 2.0 * fTemp1;
			double fTemp2 = double(input0[i0]);
			fVec0[IOTA0 & 524287] = fTemp2;
			fRec11[0] = fSlow4 + fConst4 * fRec11[1];
			double fThen1 = (((fRec8[1] == 1.0) & (fRec11[0] != fRec10[1])) ? fConst10 : 0.0);
			double fThen3 = (((fRec8[1] == 0.0) & (fRec11[0] != fRec9[1])) ? fConst9 : fThen1);
			double fElse3 = (((fRec8[1] > 0.0) & (fRec8[1] < 1.0)) ? fRec7[1] : 0.0);
			double fTemp3 = ((fRec7[1] != 0.0) ? fElse3 : fThen3);
			fRec7[0] = fTemp3;
			fRec8[0] = std::max<double>(0.0, std::min<double>(1.0, fRec8[1] + fTemp3));
			fRec9[0] = (((fRec8[1] >= 1.0) & (fRec10[1] != fRec11[0])) ? fRec11[0] : fRec9[1]);
			fRec10[0] = (((fRec8[1] <= 0.0) & (fRec9[1] != fRec11[0])) ? fRec11[0] : fRec10[1]);
			double fTemp4 = fVec0[(IOTA0 - int(std::min<double>(fConst8, std::max<double>(0.0, fRec9[0])))) & 524287];
			fRec12[0] = fSlow5 + fConst4 * fRec12[1];
			double fTemp5 = (fTemp4 + fRec8[0] * (fVec0[(IOTA0 - int(std::min<double>(fConst8, std::max<double>(0.0, fRec10[0])))) & 524287] - fTemp4)) * fRec12[0];
			fVec1[0] = fTemp5;
			double fTemp6 = fTemp5 - fVec1[1];
			double fThen6 = (std::log(std::min<double>(1.7976931348623157e+308, double(cosh(double(fTemp5))))) - std::log(std::min<double>(1.7976931348623157e+308, double(cosh(double(fVec1[1])))))) / fTemp6;
			double fElse6 = double(tanh(double(0.5 * (fTemp5 + fVec1[1]))));
			fRec15[0] = fSlow6 + fConst4 * fRec15[1];
			double fTemp7 = std::tan(fConst6 * std::pow(10.0, 3.0 * fRec15[0] + 1.0));
			double fTemp8 = ((fRec3 - fRec14[1]) * fTemp7) / (fTemp7 + 1.0);
			double fRec13 = fRec14[1] + fTemp8;
			fRec14[0] = fRec14[1] + 2.0 * fTemp8;
			double fTemp9 = (fRec3 + ((std::fabs(fTemp6) <= fConst11) ? fElse6 : fThen6) / fRec12[0]) - fRec13;
			fVec2[IOTA0 & 524287] = fTemp9;
			fRec20[0] = fSlow7 + fConst4 * fRec20[1];
			double fThen8 = (((fRec17[1] == 1.0) & (fRec20[0] != fRec19[1])) ? fConst10 : 0.0);
			double fThen10 = (((fRec17[1] == 0.0) & (fRec20[0] != fRec18[1])) ? fConst9 : fThen8);
			double fElse10 = (((fRec17[1] > 0.0) & (fRec17[1] < 1.0)) ? fRec16[1] : 0.0);
			double fTemp10 = ((fRec16[1] != 0.0) ? fElse10 : fThen10);
			fRec16[0] = fTemp10;
			fRec17[0] = std::max<double>(0.0, std::min<double>(1.0, fRec17[1] + fTemp10));
			fRec18[0] = (((fRec17[1] >= 1.0) & (fRec19[1] != fRec20[0])) ? fRec20[0] : fRec18[1]);
			fRec19[0] = (((fRec17[1] <= 0.0) & (fRec18[1] != fRec20[0])) ? fRec20[0] : fRec19[1]);
			double fTemp11 = fVec2[(IOTA0 - int(std::min<double>(fConst8, std::max<double>(0.0, fRec18[0])))) & 524287];
			fRec2[0] = fTemp11 + fRec17[0] * (fVec2[(IOTA0 - int(std::min<double>(fConst8, std::max<double>(0.0, fRec19[0])))) & 524287] - fTemp11);
			fRec21[0] = fSlow8 + fConst4 * fRec21[1];
			double fTemp12 = fRec1[0] * (fRec2[0] * fRec21[0] + fTemp2 * (1.0 - fRec21[0]));
			fVec3[0] = fTemp12;
			fRec0[0] = fConst2 * (fTemp12 - fVec3[1] + fConst12 * fRec0[1]);
			fRec26[0] = fSlow10 + fConst4 * fRec26[1];
			fRec27[0] = fSlow11 + fConst4 * fRec27[1];
			double fTemp13 = std::tan(fConst6 * std::pow(10.0, 3.0 * fRec27[0] + 1.0));
			double fTemp14 = ((fRec26[0] * fRec23[1] - fRec25[1]) * fTemp13) / (fTemp13 + 1.0);
			double fRec24 = fRec25[1] + fTemp14;
			fRec25[0] = fRec25[1] + 2.0 * fTemp14;
			double fTemp15 = double(input1[i0]);
			fVec4[IOTA0 & 524287] = fTemp15;
			fRec32[0] = fSlow12 + fConst4 * fRec32[1];
			double fThen14 = (((fRec29[1] == 1.0) & (fRec32[0] != fRec31[1])) ? fConst10 : 0.0);
			double fThen16 = (((fRec29[1] == 0.0) & (fRec32[0] != fRec30[1])) ? fConst9 : fThen14);
			double fElse16 = (((fRec29[1] > 0.0) & (fRec29[1] < 1.0)) ? fRec28[1] : 0.0);
			double fTemp16 = ((fRec28[1] != 0.0) ? fElse16 : fThen16);
			fRec28[0] = fTemp16;
			fRec29[0] = std::max<double>(0.0, std::min<double>(1.0, fRec29[1] + fTemp16));
			fRec30[0] = (((fRec29[1] >= 1.0) & (fRec31[1] != fRec32[0])) ? fRec32[0] : fRec30[1]);
			fRec31[0] = (((fRec29[1] <= 0.0) & (fRec30[1] != fRec32[0])) ? fRec32[0] : fRec31[1]);
			double fTemp17 = fVec4[(IOTA0 - int(std::min<double>(fConst8, std::max<double>(0.0, fRec30[0])))) & 524287];
			double fTemp18 = fRec12[0] * (fTemp17 + fRec29[0] * (fVec4[(IOTA0 - int(std::min<double>(fConst8, std::max<double>(0.0, fRec31[0])))) & 524287] - fTemp17));
			fVec5[0] = fTemp18;
			double fTemp19 = fTemp18 - fVec5[1];
			double fThen19 = (std::log(std::min<double>(1.7976931348623157e+308, double(cosh(double(fTemp18))))) - std::log(std::min<double>(1.7976931348623157e+308, double(cosh(double(fVec5[1])))))) / fTemp19;
			double fElse19 = double(tanh(double(0.5 * (fTemp18 + fVec5[1]))));
			fRec35[0] = fSlow13 + fConst4 * fRec35[1];
			double fTemp20 = std::tan(fConst6 * std::pow(10.0, 3.0 * fRec35[0] + 1.0));
			double fTemp21 = ((fRec24 - fRec34[1]) * fTemp20) / (fTemp20 + 1.0);
			double fRec33 = fRec34[1] + fTemp21;
			fRec34[0] = fRec34[1] + 2.0 * fTemp21;
			double fTemp22 = (fRec24 + ((std::fabs(fTemp19) <= fConst11) ? fElse19 : fThen19) / fRec12[0]) - fRec33;
			fVec6[IOTA0 & 524287] = fTemp22;
			fRec40[0] = fSlow14 + fConst4 * fRec40[1];
			double fThen21 = (((fRec37[1] == 1.0) & (fRec40[0] != fRec39[1])) ? fConst10 : 0.0);
			double fThen23 = (((fRec37[1] == 0.0) & (fRec40[0] != fRec38[1])) ? fConst9 : fThen21);
			double fElse23 = (((fRec37[1] > 0.0) & (fRec37[1] < 1.0)) ? fRec36[1] : 0.0);
			double fTemp23 = ((fRec36[1] != 0.0) ? fElse23 : fThen23);
			fRec36[0] = fTemp23;
			fRec37[0] = std::max<double>(0.0, std::min<double>(1.0, fRec37[1] + fTemp23));
			fRec38[0] = (((fRec37[1] >= 1.0) & (fRec39[1] != fRec40[0])) ? fRec40[0] : fRec38[1]);
			fRec39[0] = (((fRec37[1] <= 0.0) & (fRec38[1] != fRec40[0])) ? fRec40[0] : fRec39[1]);
			double fTemp24 = fVec6[(IOTA0 - int(std::min<double>(fConst8, std::max<double>(0.0, fRec38[0])))) & 524287];
			fRec23[0] = fTemp24 + fRec37[0] * (fVec6[(IOTA0 - int(std::min<double>(fConst8, std::max<double>(0.0, fRec39[0])))) & 524287] - fTemp24);
			fRec41[0] = fSlow15 + fConst4 * fRec41[1];
			double fTemp25 = fRec1[0] * (fRec23[0] * fRec41[0] + fTemp15 * (1.0 - fRec41[0]));
			fVec7[0] = fTemp25;
			fRec22[0] = fConst2 * (fTemp25 - fVec7[1] + fConst12 * fRec22[1]);
			double fTemp26 = fSlow9 * (fRec0[0] + fRec22[0]);
			output0[i0] = FAUSTFLOAT(fSlow0 * fRec0[0] + fTemp26);
			output1[i0] = FAUSTFLOAT(fTemp26 + fSlow0 * fRec22[0]);
			fRec1[1] = fRec1[0];
			fRec5[1] = fRec5[0];
			fRec6[1] = fRec6[0];
			fRec4[1] = fRec4[0];
			IOTA0 = IOTA0 + 1;
			fRec11[1] = fRec11[0];
			fRec7[1] = fRec7[0];
			fRec8[1] = fRec8[0];
			fRec9[1] = fRec9[0];
			fRec10[1] = fRec10[0];
			fRec12[1] = fRec12[0];
			fVec1[1] = fVec1[0];
			fRec15[1] = fRec15[0];
			fRec14[1] = fRec14[0];
			fRec20[1] = fRec20[0];
			fRec16[1] = fRec16[0];
			fRec17[1] = fRec17[0];
			fRec18[1] = fRec18[0];
			fRec19[1] = fRec19[0];
			fRec2[1] = fRec2[0];
			fRec21[1] = fRec21[0];
			fVec3[1] = fVec3[0];
			fRec0[1] = fRec0[0];
			fRec26[1] = fRec26[0];
			fRec27[1] = fRec27[0];
			fRec25[1] = fRec25[0];
			fRec32[1] = fRec32[0];
			fRec28[1] = fRec28[0];
			fRec29[1] = fRec29[0];
			fRec30[1] = fRec30[0];
			fRec31[1] = fRec31[0];
			fVec5[1] = fVec5[0];
			fRec35[1] = fRec35[0];
			fRec34[1] = fRec34[0];
			fRec40[1] = fRec40[0];
			fRec36[1] = fRec36[0];
			fRec37[1] = fRec37[0];
			fRec38[1] = fRec38[0];
			fRec39[1] = fRec39[0];
			fRec23[1] = fRec23[0];
			fRec41[1] = fRec41[0];
			fVec7[1] = fVec7[0];
			fRec22[1] = fRec22[0];
		}
	}

};

// END-FAUSTDSP

#endif
