//
//  ByteBuffer.h
//  NetWorkFrame
//

#pragma once

#include <vector>
#include "GUtils.h"

class ByteBuffer{
protected:
    size_t                  BRPos;
    size_t                  BWPos;
    std::vector<uint8_t>	BData;
    
public:
    ByteBuffer(): BRPos(0),BWPos(0){}
    ByteBuffer(size_t res): BRPos(0),BWPos(0){
        BData.reserve(res);
    }
    ByteBuffer(const ByteBuffer &buf):BRPos(buf.BRPos),BWPos(buf.BWPos),BData(buf.BData){}
    ~ByteBuffer(){}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
public:
    const uint8_t* contents() const { return &BData[BRPos]; }
    
    size_t size() const { return BData.size(); }
    
    bool empty() const { return BData.empty(); }
    
    void clear(){
        BData.clear();
        BRPos = BWPos = 0;
    }
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template <typename T>
    void append(T value){
        append((uint8_t*)&value, sizeof(value));
    }
    void append(const ByteBuffer& buffer){
        if (buffer.size()) append(buffer.contents(),buffer.size());
    }
    void append(const uint8_t *src, size_t cnt){
        if (!cnt) return;
//        assert(size() < 10000000);
        if (BData.size() < BWPos + cnt){
            BData.resize(BWPos + cnt);
        }
        memcpy(&BData[BWPos], src, cnt);
        BWPos += cnt;
    }
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template <typename T> T read(){
        T r = read<T>(BRPos);
        BRPos += sizeof(T);
        return r;
    };
    template <typename T> T read(size_t pos) const{
//        assert(pos + sizeof(T) <= size() || PrintPosError(false,pos,sizeof(T)));
        return *((T const*)&BData[pos]);
    }
    
    void read(uint8_t *dest, size_t len){
//        assert(BRPos  + len  <= size() || PrintPosError(false, BRPos,len));
        memcpy(dest, &BData[BRPos], len);
        BRPos += len;
    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
public:
    ByteBuffer& operator<<(bool value){
        append<char>((char)value);
        return *this;
    }
    ByteBuffer& operator<<(uint8_t value){
        append<uint8_t>(value);
        return *this;
    }
    ByteBuffer& operator<<(uint16_t value){
        append<uint16_t>(value);
        return *this;
    }
    ByteBuffer& operator<<(uint32_t value){
        append<uint32_t>(value);
        return *this;
    }
    ByteBuffer& operator<<(uint64_t value){
        append<uint64_t>(value);
        return *this;
    }
    
    ByteBuffer& operator<<(int8_t value){
        append<int8_t>(value);
        return *this;
    }
    ByteBuffer& operator<<(int16_t value){
        append<int16_t>(value);
        return *this;
    }
    ByteBuffer& operator<<(int32_t value){
        append<int32_t>(value);
        return *this;
    }
    ByteBuffer& operator<<(int64_t value){
        append<int64_t>(value);
        return *this;
    }
    
    ByteBuffer& operator<<(float value){
        append<float>(value);
        return *this;
    }
    ByteBuffer& operator<<(double value){
        append<double>(value);
        return *this;
    }
    ByteBuffer& operator<<(time_t value){
        append<time_t>(value);
        return *this;
    }
    
    ByteBuffer& operator<<(const std::string& value){
        append((uint8_t const *)value.c_str(), value.length());
        append((uint8_t)0);
        return *this;
    }
    ByteBuffer& operator<<(const char* str){
        append( (uint8_t const *)str, str ? strlen(str) : 0);
        append((uint8_t)0);
        return *this;
    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
public:
    ByteBuffer& operator>>(bool& value){
        value = read<char>() > 0 ? true : false;
        return *this;
    }
    ByteBuffer& operator>>(uint8_t& value){
        value = read<uint8_t>();
        return *this;
    }
    ByteBuffer& operator>>(uint16_t& value){
        value = read<uint16_t>();
        return *this;
    }
    ByteBuffer& operator>>(uint32_t& value){
        value = read<uint32_t>();
        return *this;
    }
    ByteBuffer& operator>>(uint64_t& value){
        value = read<uint64_t>();
        return *this;
    }
    
    ByteBuffer& operator>>(int8_t& value){
        value = read<int8_t>();
        return *this;
    }
    ByteBuffer& operator>>(int16_t& value){
        value = read<int16_t>();
        return *this;
    }
    ByteBuffer& operator>>(int32_t& value){
        value = read<int32_t>();
        return *this;
    }
    ByteBuffer& operator>>(int64_t& value){
        value = read<int64_t>();
        return *this;
    }
    
    ByteBuffer& operator>>(float& value){
        value = read<float>();
        return *this;
    }
    ByteBuffer& operator>>(double& value){
        value = read<double>();
        return *this;
    }
    ByteBuffer& operator>>(time_t& value){
        value = read<time_t>();
        return *this;
    }
    ByteBuffer& operator>>(std::string& value){
        value.clear();
        while (BRPos < size()){
            char c = read<char>();
            if (c == 0){
                break;
            }
            value += c;
        }
        return *this;
    }
    ByteBuffer& operator>>(char value[]){
        std::string strValue;
        strValue.clear();
        while (BRPos < size()){
            char c = read<char>();
            if (c == 0){
                break;
            }
            strValue += c;
        }
        strncpy(value, strValue.c_str(), strValue.size());
        return *this;
    }
};

//////////////////////////////////////////////////////////////////////////
// std::vector
//////////////////////////////////////////////////////////////////////////
#ifdef _VECTOR_
template <typename T>
ByteBuffer& operator<<(ByteBuffer& b, const std::vector<T>& v)
{
    b << (uint32)v.size();
    
    typename std::vector<T>::const_iterator iter	= v.begin();
    typename std::vector<T>::const_iterator& iEnd	= v.end();
    for (; iter != iEnd; ++iter)
    {
        b << *iter;
    }
    return b;
}

template <typename T>
ByteBuffer& operator>>(ByteBuffer& b, std::vector<T>& v)
{
    uint32 vsize;
    b >> vsize;
    v.clear();
    while (vsize--)
    {
        T t;
        b >> t;
        v.push_back(t);
    }
    return b;
}
#endif

//////////////////////////////////////////////////////////////////////////
// std::list
//////////////////////////////////////////////////////////////////////////
#ifdef _LIST_
template <typename T>
ByteBuffer& operator<<(ByteBuffer& b, const std::list<T>& v)
{
    b << (uint32)v.size();
    
    typename std::list<T>::const_iterator iter	= v.begin();
    typename std::list<T>::const_iterator& iEnd	= v.end();
    for (; iter != iEnd; ++iter)
    {
        b << *iter;
    }
    return b;
}

template <typename T>
ByteBuffer& operator>>(ByteBuffer& b, std::list<T>& v)
{
    uint32 vsize;
    b >> vsize;
    v.clear();
    while (vsize--)
    {
        T t;
        b >> t;
        v.push_back(t);
    }
    return b;
}
#endif

//////////////////////////////////////////////////////////////////////////
// std::map
//////////////////////////////////////////////////////////////////////////
#ifdef _MAP_
template <typename K, typename V>
ByteBuffer& operator<<(ByteBuffer& b, const std::map<K, V>& m)
{
    b << (uint32)m.size();
    
    typename std::map<K, V>::const_iterator iter = m.begin();
    typename std::map<K, V>::const_iterator iEnd = m.end();
    for (; iter != iEnd; ++iter)
    {
        b << iter->first << iter->second;
    }
    return b;
}

template <typename K, typename V>
ByteBuffer &operator>>(ByteBuffer& b, std::map<K, V>& m)
{
    uint32 msize;
    b >> msize;
    m.clear();
    while (msize--)
    {
        K k;
        V v;
        b >> k >> v;
        m.insert(std::make_pair(k, v));
    }
    return b;
}
#endif
