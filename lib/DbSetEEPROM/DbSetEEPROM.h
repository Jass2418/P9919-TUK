#ifndef DBSETEEPROM_H
#define DBSETEEPROM_H

#include <EEPROM.h>

template <class T>
class DbSetEEPROM {
    public:
    DbSetEEPROM(int rowAmount){
        _rowAmount=rowAmount;
        _size=sizeof(T);
        _initialPosition=_lastPositionMemory;
        _lastPositionMemory= (rowAmount * _size)+_initialPosition + 1;
        _lastPosition=_lastPositionMemory;
    }
    DbSetEEPROM(int rowAmount, int lastPosition){
        _rowAmount=rowAmount;
        _size=sizeof(T);
        _initialPosition=lastPosition;
        _lastPositionMemory= (rowAmount * _size)+_initialPosition + 1;
        _lastPosition=_lastPositionMemory;
    }
    
    void add(const T & value){

        uint8_t indexValue =EEPROM.read(_initialPosition);
        int indexMemory;

        if(indexValue>=_rowAmount){
            indexMemory=_initialPosition+1;
            indexValue=0;
            EEPROM.write(_initialPosition,indexValue);
        }
        else
            indexMemory=indexValue*_size + _initialPosition+1;
        
        ///Insert Object
        EEPROM.put(indexMemory,value);
        ///Insert Index value
        EEPROM.write(_initialPosition,indexValue+1);        
    }
    
    T remove(int index = 0){
        T object;
        if(index<0 || index>_rowAmount)
            return object;
        
        int address = index * _size + _initialPosition+1;
        EEPROM.get(address,object);
        for(int i=0;i<_size;i++){
            EEPROM.write(address+i,0xFF);
        }
        return object;
    }
    
    T get(int index = 0){
        T object;
        if(index<0 || index>_rowAmount-1)
            return object;

        int address = index * _size + _initialPosition+1;
        EEPROM.get(address,object);
        return object;
    }

    T* getLasts(int amount){
        T obj;
        T *buffer=NULL;
        buffer=new T[amount];
        int indexValue = EEPROM.read(_initialPosition)-1;
        for(int i=0;i<amount;i++){
            if(indexValue<0)
                indexValue=_rowAmount-1;
            buffer[i]=get(indexValue);
            indexValue--;  
        }
        return buffer;
    }

    T* getAll(){
        T *buffer=NULL;
        buffer=new T[_rowAmount];
        for(int i=0;i<_rowAmount;i++){
            buffer[i]=get(i);
        }
        return buffer;
    }
    
    void update(int index,const T & value){
        if(index<0 || index>_rowAmount-1)
            return;

        int address = index * _size + _initialPosition+1;
        EEPROM.put(address,value);
    }

    int lastPosition(){
        return _lastPosition;
    }
    
    private:
        int _rowAmount;
        int _size;
        int _initialPosition;
        int _lastPosition;

        static int _lastPositionMemory;
};

template <class T>
int DbSetEEPROM<T>::_lastPositionMemory=0;

#endif