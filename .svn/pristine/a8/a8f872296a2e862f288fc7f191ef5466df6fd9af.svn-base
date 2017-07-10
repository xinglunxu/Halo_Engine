//
//  Engine.hpp
//  Halo_Engine
//
//  Created by 许兴伦 on 7/4/17.
//  Copyright © 2017 SparkLight. All rights reserved.
//

#ifndef Engine_hpp
#define Engine_hpp

#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include "ISystem.hpp"
#include <list>
#include <unordered_set>
#include <unordered_map>
#include <typeindex>
#include <functional>

using namespace std;


template <class ... A>
struct AddEntityClass;



class Engine{
    friend struct AddEntityClass<>;
    template <class ... A> friend struct AddEntityClass;
public:
    void Run();
    Engine();
    template <typename T> void AddSystem();
    template <typename T> void AddData();
    template <typename ... types> int AddEntity();
    
private:
    int frame_num;
    void Update();
    unordered_map<type_index, ISystem*>* systems;
    unordered_map<type_index, void*>* datas;
    unordered_map<type_index, function<void(int)>> dataFunctions;
    static int nextId;
    template <typename T, typename ... res> void _AddEntity(int id);
    template <typename dataType> void AddEntityData(int id);
};



//–––––––––––––––––––––––––––––––––––––
//Template Initiation
//-------------------------------------

template <typename... A>
struct AddEntityClass {
public:
    static void call(int id, Engine* engine){
        engine->_AddEntity<A...>(id);
    }
};

template <>
struct AddEntityClass<> {
public:
    static void call(int id, Engine* engine){}
};


template <typename T>
void Engine::AddSystem(){
    T* system = new T();
    (*systems)[type_index(typeid(T))] = system;
    std::list<type_index>* typeInfos = system->GetDataTypes();
    std::list<void*>* datasList = new std::list<void*>();
    for(auto it = typeInfos->begin(); it!=typeInfos->end();it++){
        type_index ti = *it;
        datasList->insert(datasList->end(), (*datas)[ti]);
    }
    system->InjectData(datasList);
}


template <typename T>
void Engine::AddData(){
    unordered_map<int, T*>* data = new unordered_map<int, T*>;
    void* dataP = static_cast<void*>(data);
    (*datas)[type_index(typeid(T))] = dataP;
    type_index ti = type_index(typeid(T));
    dataFunctions[ti] = [this](int id){
        this->AddEntityData<T>(id);
    };
}


template <typename ... types>
int Engine::AddEntity(){
    int entityId = (nextId++);
    _AddEntity<types...>(entityId);
    return entityId;
}

//private____________________________________

template <typename T, typename ... res>
void Engine::_AddEntity(int id){
    ISystem *system = (*systems)[type_index(typeid(T))];
    system->AddEntity(id);
    list<type_index>* dataTypes = system->GetDataTypes();
    for(auto it = dataTypes->begin(); it!=dataTypes->end();it++){
        type_index ti = *it;
        dataFunctions[ti](id);
    }
    AddEntityClass<res...>::call(id, this);
}


template <typename dataType>
void Engine::AddEntityData(int id){
    type_index ti = type_index(typeid(dataType));
    void* dataP = (*datas)[ti];
    unordered_map<int, dataType*>* data = static_cast<unordered_map<int, dataType*>*>(dataP);
    if(data->find(id)==data->end()){
        (*data)[id] = new dataType();
    }
}


#endif /* Engine_hpp */
