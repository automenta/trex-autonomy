/* -*- C++ -*-
 * $Id$
 */
/** @file "EuropaXML.cc"
 *
 *
 * @author Frederic Py <fpy@mbari.org>
 */
#include "EuropaXML.hh"

#include "BoolDomain.hh"
#include "IntervalIntDomain.hh"
#include "Object.hh"

#include "Utils.hh"

using namespace TREX;

namespace {

  size_t id_gen() {
    static size_t count(0);
    return ++count;	       
  }

  bool is_bool(std::string const &typeName) {
    return typeName=="bool" || typeName=="BOOL" || 
      typeName==BoolDomain::getDefaultTypeName().toString();
  } // ::is_bool

  bool is_int(std::string const &typeName) {
    return typeName=="int" || typeName=="INT_INTERVAL" ||
      typeName==IntervalIntDomain::getDefaultTypeName().toString();
  } // ::is_int

  std::string bool_val_to_str(double value) {
    return value?"true":"false";
  }

  std::string int_val_to_str(double value) {
    std::ostringstream oss;
    oss<<static_cast<int>(value);
    return oss.str();
  }

  std::string double_val_to_str(double value) {
    std::ostringstream oss;
    oss.setf(std::ios::fixed);
    oss<<value;
    return oss.str();
  }

  std::string string_val_to_str(double value) {
    LabelStr const &str = value;
    return str.toString();
  }

  std::string object_val_to_str(double value) {
    ObjectId object = value;
    return object->getName().toString();
  }

  TiXmlElement *domain_val_to_xml(AbstractDomain const &domain, double value) {
    LabelStr typeName = domain.getTypeName();
    TiXmlElement *elem;
    

    if( domain.isEntity() ) {
      elem = new TiXmlElement("object");
      elem->SetAttribute("value", object_val_to_str(value).c_str()); // may be replaced by domain_val_to_str
    } else {
      std::string strName = typeName.toString();
      
      if( is_bool(strName) ) {
	elem = new TiXmlElement("value");
	
	elem->SetAttribute("type", "bool");
	elem->SetAttribute("name", bool_val_to_str(value).c_str());
      } else if( domain.isNumeric() ) {
	elem = new TiXmlElement("value");
	
	elem->SetAttribute("type", strName.c_str());
	if( is_int(strName) )
	  elem->SetAttribute("name", int_val_to_str(value).c_str());
	else
	  elem->SetAttribute("name", double_val_to_str(value).c_str());
      } else {
	elem = new TiXmlElement("symbol");

	elem->SetAttribute("type", strName.c_str());
	elem->SetAttribute("value", string_val_to_str(value).c_str()); // may be replaced by domain_val_to_str
      }
    }
    return elem;
  } // ::domain_val_to_xml

  void domain_val_print_xml(FILE *out, AbstractDomain const &domain, double value) {
    LabelStr typeName = domain.getTypeName();
    
    if( domain.isEntity() ) {
      fprintf(out, "<object value=\"%s\" />",
	      object_val_to_str(value).c_str()); // may be replaced by domain_val_to_str
    } else {
      std::string strName = typeName.toString();
      
      if( is_bool(strName) ) {
	fprintf(out, "<value type=\"bool\" name=\"%s\" />",
		bool_val_to_str(value).c_str());
      } else if( domain.isNumeric() ) {
	fprintf(out, "<value type=\"%s\" name=\"",
		strName.c_str());
	if( is_int(strName) )
	  fprintf(out, "%s\" />", int_val_to_str(value).c_str());
	else
	  fprintf(out, "%s\" />", double_val_to_str(value).c_str());
      } else 
	fprintf(out, "<symbol type=\"%s\" value=\"%s\" />", strName.c_str(),
		string_val_to_str(value).c_str()); // may be replaced by domain_val_to_str
    }
  } // ::domain_val_print_xml

} // <unnamed>

namespace TREX { 
  
  std::string domain_val_to_str(AbstractDomain const &domain, double value, 
				bool symbolic) {
    std::string typeName = domain.getTypeName().toString();

    if( is_bool(typeName) )
      return bool_val_to_str(value);
    else if( domain.isNumeric() ) {
      if( symbolic && PLUS_INFINITY==value )
	return "+inf";
      else if( symbolic && MINUS_INFINITY==value )
	return "-inf";
      else if( is_int(typeName) )
	return int_val_to_str(value);
      else
	return double_val_to_str(value);
    } else if( LabelStr::isString(domain.getUpperBound()) )
      return string_val_to_str(value);
    else 
      return object_val_to_str(value);
  } // TREX::domain_val_to_str

  TiXmlElement *to_xml(AbstractDomain const &domain) {
    if( !domain.isEmpty() ) {
      if( domain.isSingleton() ) 
	return domain_val_to_xml(domain, domain.getSingletonValue());
      else if( domain.isEnumerated() ) {
	TiXmlElement *elem = new TiXmlElement("set");
	std::string typeName = domain.getTypeName().toString();
	std::list<double> values;
	std::list<double>::const_iterator i, endi;
	
	domain.getValues(values);
	
	elem->SetAttribute("type", typeName.c_str());
	for( i=values.begin(), endi=values.end(); endi!=i; ++i ) 
	  elem->LinkEndChild(domain_val_to_xml(domain, *i));
	return elem;
      } else if( domain.isInterval() ) {
	TiXmlElement *elem = new TiXmlElement("interval");
	std::string typeName = domain.getTypeName().toString();
	
	elem->SetAttribute("type", typeName.c_str());
	elem->SetAttribute("min", domain_val_to_str(domain, domain.getLowerBound()).c_str());
	elem->SetAttribute("max", domain_val_to_str(domain, domain.getUpperBound()).c_str());
	return elem;
      }
    }
    return NULL;
  } // TREX::to_xml<AbstractDomain>

  void print_xml(FILE *out, AbstractDomain const &domain) {
    checkError(!domain.isEmpty(), "print_xml<AbstractDomain>: Unknown domain type.");
    if( domain.isSingleton() )
      domain_val_print_xml(out, domain, domain.getSingletonValue());
    else if( domain.isEnumerated() ) {
      std::list<double> values;

      domain.getValues(values);
      
      if( !values.empty() ) {
	std::list<double>::const_iterator i=values.begin(), endi = values.end();
	
	fprintf(out, "<set type=\"%s\">", domain.getTypeName().c_str());
	for( ; endi!=i; ++i )
	  domain_val_print_xml(out, domain, *i);
	fprintf(out, "</set>");
      } else 
	fprintf(out, "<set type=\"%s\"/>", domain.getTypeName().c_str());
    } else if( domain.isInterval() ) 
      fprintf(out, "<interval type=\"%s\" min=\"%s\" max=\"%s\"/>",
	      domain.getTypeName().c_str(), 
	      domain_val_to_str(domain, domain.getLowerBound()).c_str(),
	      domain_val_to_str(domain, domain.getUpperBound()).c_str());
  } // TREX::print_xml<AbstractDomain>

  TiXmlNode const *firstPath(TiXmlNode const *elem, std::string const &path) {
    std::vector<std::string> attrs;

    tokenize(path, attrs, "/");

    for(std::vector<std::string>::const_iterator i=attrs.begin(), endi=attrs.end();
	NULL!=elem && endi!=i; ++i ) 
      elem = elem->FirstChild(i->c_str());
    return elem;
  }


} // TREX

