/*
 * Copyright 2013 Open Source Robotics Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
*/

#ifndef GZBRIDGE_PB2JSON_HH_
#define GZBRIDGE_PB2JSON_HH_

#include <memory>

#include <google/protobuf/descriptor.h>
#include <google/protobuf/message.h>
#include <jansson.h>

namespace gzweb
{
  std::string pb2json(const google::protobuf::Message &msg);

  std::string pb2json(google::protobuf::Message *msg,const char *buf,int len);

  std::string get_value(const std::string &msg, const std::string &key);

  json_t *parse_msg(const google::protobuf::Message *msg);

  json_t *parse_repeated_field(const google::protobuf::Message *msg,
      const google::protobuf::Reflection *ref,
      const google::protobuf::FieldDescriptor *field);


  // forward declaration
  class JsonObjPrivate;

  /// \brief C++ interface for manipulating json object
  class JsonObj
  {
    /// \brief Constructor
    /// \param[in] _str input json string
    public: JsonObj(const std::string &_str);

    /// \brief Copy constructor
    /// \param[in] _other Othher JsonObj
    public: JsonObj(const JsonObj &_other);

    /// \brief Destructor
    public: ~JsonObj();

    /// \brief Get child json object
    /// \param[in] _key Json key
    /// \return JsonObj
    public: JsonObj Object(const std::string &_key) const;

    /// \brief Get number value
    /// \return double value
    public: double Number() const;

    /// \brief Get bool value
    /// \return bool value
    public: bool Bool() const;

    /// \brief Get string value
    /// \return string value
    public: std::string String() const;

    /// \brief Get array json object at specified index
    /// \param[in] _index Index in the array
    /// \return JsonObj
    public: JsonObj ArrayObject(const unsigned int _index) const;

    /// \brief Get the size of the array
    /// \return Size of array
    public: unsigned int ArraySize() const;

    /// \brief bool operator
    /// \return True if pointer to json object is not null
    public: operator bool() const;

    /// \brief Private constructor
    /// \param[in] _obj Internal json object
    private: JsonObj(json_t *_obj);

    /// \brief Internal private data pointer.
    private: std::unique_ptr<JsonObjPrivate> dataPtr;
  };
}

#endif
