#include "private/VIMacro.h"
#include <memory>
#define VI_Base_Q(T) \
protected: T* q_ptr; 
#define VI_Base_D(T) \
protected: std::unique_ptr<T##Private> d_ptr;

#define VI_Init_D(T) \
d_ptr = std::make_unique<T##Private>(); \
d_ptr->q_ptr = this;

#define VI_Has_Child(T)\
protected: def_init T(const T##Private&& d);
#define VI_IMPL(T) \
friend class T; \
private: inline T* Q() { return reinterpret_cast<T*>(q_ptr); } \
private: inline const T* Q() const { return reinterpret_cast<const T*>(q_ptr); }

#define VI_DECL(T) \
friend class T##Private; \
private: inline T##Private* D() { return reinterpret_cast<T##Private*>(d_ptr); } \
private: inline const T##Private* D() const { return reinterpret_cast<const T##Private*>(d_ptr); }

class TemplateObject;
class TemplateDataObject
{
    friend class TemplateObject;
    _Protected TemplateObject * q_ptr;
};
template<typename T>
concept TemplateDataObjectChilds = requires(T t){
    requires std::is_base_of_v<TemplateDataObject, T>;
};

class TemplateObject 
{
    _Protected std::unique_ptr<TemplateDataObject> d_ptr;
    _Public def_init TemplateObject(){
        d_ptr = std::make_unique<TemplateDataObject>();
        d_ptr->q_ptr = this;
    }
    _Protected def_init TemplateObject(TemplateDataObject* d){
        d_ptr = std::unique_ptr<TemplateDataObject>(d);
    }
    _Protected template<TemplateDataObjectChilds T> T* getD(){
        return reinterpret_cast<T*>(d_ptr);
    }
};

class Template2Object;
class Template2DataObject :public TemplateDataObject
{
    friend class Template2Object;
};

class Template2Object :public TemplateObject
{
    _Public def_init Template2Object():TemplateObject(new Template2DataObject){
        
    }
    _Public def_del Template2Object(){

    }
    Q_D();
};