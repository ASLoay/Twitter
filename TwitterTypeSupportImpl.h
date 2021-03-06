/* -*- C++ -*- */
/* Generated by C:\Users\lashmawy\Documents\Soft\OpenDDS\bin\opendds_idl version 3.10 (ACE version 6.2a_p11) running on input file Twitter.idl */
#ifndef OPENDDS_IDL_GENERATED_TWITTERTYPESUPPORTIMPL_H_XL5EQK
#define OPENDDS_IDL_GENERATED_TWITTERTYPESUPPORTIMPL_H_XL5EQK
#include "TwitterC.h"
#include "dds/DCPS/Definitions.h"
#include "TwitterTypeSupportC.h"
#include "dds/DCPS/Serializer.h"
#include "dds/DCPS/TypeSupportImpl.h"


/* Begin MODULE: CORBA */


/* End MODULE: CORBA */


/* Begin MODULE: Twitter */



/* Begin STRUCT: Tweet */

OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

void gen_find_size(const Twitter::Tweet& stru, size_t& size, size_t& padding);

bool operator<<(Serializer& strm, const Twitter::Tweet& stru);

bool operator>>(Serializer& strm, Twitter::Tweet& stru);

size_t gen_max_marshaled_size(const Twitter::Tweet& stru, bool align);

size_t gen_max_marshaled_size(KeyOnly<const Twitter::Tweet> stru, bool align);

void gen_find_size(KeyOnly<const Twitter::Tweet> stru, size_t& size, size_t& padding);

bool operator<<(Serializer& strm, KeyOnly<const Twitter::Tweet> stru);

bool operator>>(Serializer& strm, KeyOnly<Twitter::Tweet> stru);

template <>
struct MarshalTraits<Twitter::Tweet> {
  static bool gen_is_bounded_size() { return false; }
  static bool gen_is_bounded_key_size() { return false; }
};
}  }
OPENDDS_END_VERSIONED_NAMESPACE_DECL


namespace Twitter {
// This structure supports use of std::map with a key
// defined by one or more #pragma DCPS_DATA_KEY lines.
struct  Tweet_OpenDDS_KeyLessThan {
  bool operator()(const Twitter::Tweet& v1, const Twitter::Tweet& v2) const
  {
    using ::operator<; // TAO::String_Manager's operator< is in global NS
    if (v1.owner < v2.owner) return true;
    if (v2.owner < v1.owner) return false;
    return false;
  }
};
}


namespace Twitter {
class TweetTypeSupportImpl;
}

OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {
template <>
struct DDSTraits<Twitter::Tweet> {
  typedef Twitter::Tweet MessageType;
  typedef Twitter::TweetSeq MessageSequenceType;
  typedef Twitter::TweetTypeSupport TypeSupportType;
  typedef Twitter::TweetTypeSupportImpl TypeSupportTypeImpl;
  typedef Twitter::TweetDataWriter DataWriterType;
  typedef Twitter::TweetDataReader DataReaderType;
  typedef Twitter::Tweet_OpenDDS_KeyLessThan LessThanType;

  static const char* type_name () { return "Twitter::Tweet"; }
  static bool gen_has_key () { return true; }

  static size_t gen_max_marshaled_size(const MessageType& x, bool align) { return ::OpenDDS::DCPS::gen_max_marshaled_size(x, align); }
  static void gen_find_size(const MessageType& arr, size_t& size, size_t& padding) { ::OpenDDS::DCPS::gen_find_size(arr, size, padding); }

  static size_t gen_max_marshaled_size(const OpenDDS::DCPS::KeyOnly<const MessageType>& x, bool align) { return ::OpenDDS::DCPS::gen_max_marshaled_size(x, align); }
  static void gen_find_size(const OpenDDS::DCPS::KeyOnly<const MessageType>& arr, size_t& size, size_t& padding) { ::OpenDDS::DCPS::gen_find_size(arr, size, padding); }
};
}  }
OPENDDS_END_VERSIONED_NAMESPACE_DECL


namespace Twitter {
class  TweetTypeSupportImpl
  : public virtual OpenDDS::DCPS::LocalObject<TweetTypeSupport>
  , public virtual OpenDDS::DCPS::TypeSupportImpl
{
public:
  typedef OpenDDS::DCPS::DDSTraits<Tweet> TraitsType;
  typedef TweetTypeSupport TypeSupportType;
  typedef TweetTypeSupport::_var_type _var_type;
  typedef TweetTypeSupport::_ptr_type _ptr_type;

  TweetTypeSupportImpl() {}
  virtual ~TweetTypeSupportImpl() {}

  virtual ::DDS::DataWriter_ptr create_datawriter();
  virtual ::DDS::DataReader_ptr create_datareader();
#ifndef OPENDDS_NO_MULTI_TOPIC
  virtual ::DDS::DataReader_ptr create_multitopic_datareader();
#endif /* !OPENDDS_NO_MULTI_TOPIC */
#ifndef OPENDDS_NO_CONTENT_SUBSCRIPTION_PROFILE
  virtual const OpenDDS::DCPS::MetaStruct& getMetaStructForType();
#endif /* !OPENDDS_NO_CONTENT_SUBSCRIPTION_PROFILE */
  virtual bool has_dcps_key();
  const char* default_type_name() const;
  static TweetTypeSupport::_ptr_type _narrow(CORBA::Object_ptr obj);
};
}

#ifndef OPENDDS_NO_CONTENT_SUBSCRIPTION_PROFILE
OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

class MetaStruct;

template<typename T>
const MetaStruct& getMetaStruct();

template<>
const MetaStruct& getMetaStruct<Twitter::Tweet>();
void gen_skip_over(Serializer& ser, Twitter::Tweet*);

}  }
OPENDDS_END_VERSIONED_NAMESPACE_DECL

#endif

/* End STRUCT: Tweet */

/* End MODULE: Twitter */
#endif /* OPENDDS_IDL_GENERATED_TWITTERTYPESUPPORTIMPL_H_XL5EQK */
