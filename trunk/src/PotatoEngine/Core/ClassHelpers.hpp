#ifndef __CLASSHELPERS__
#define __CLASSHELPERS__

#define SAFETY_CHECK(VAR)					assert(VAR != nullptr)

// Accessor helpers
#define ACCESSOR(TYPE, MEMBER)					ACCESSOR_WITH_NAME(TYPE, MEMBER, MEMBER)
#define REF_ACCESSOR(TYPE, MEMBER)				REF_ACCESSOR_WITH_NAME(TYPE, MEMBER, MEMBER)
#define PTR_ACCESSOR(TYPE, MEMBER)				PTR_ACCESSOR_WITH_NAME(TYPE, MEMBER, MEMBER)
#define CONST_ACCESSOR(TYPE, MEMBER)			CONST_ACCESSOR_WITH_NAME(TYPE, MEMBER, MEMBER)
#define CONST_REF_ACCESSOR(TYPE, MEMBER)		CONST_REF_ACCESSOR_WITH_NAME(TYPE, MEMBER, MEMBER)
#define CONST_PTR_ACCESSOR(TYPE, MEMBER)		CONST_PTR_ACCESSOR_WITH_NAME(TYPE, MEMBER, MEMBER)
#define SIMPLE_CONST_ACCESSOR(TYPE, MEMBER)		SIMPLE_CONST_ACCESSOR_WITH_NAME(TYPE, MEMBER, MEMBER)

#define ACCESSOR_WITH_NAME(TYPE, MEMBER, NAME)					FULLY_CUSTOMIZED_ACCESSOR(TYPE, MEMBER, NAME, public, private,      ,  ,      , ,  )
#define REF_ACCESSOR_WITH_NAME(TYPE, MEMBER, NAME)				FULLY_CUSTOMIZED_ACCESSOR(TYPE, MEMBER, NAME, public, private,      , &,      , ,  )
#define PTR_ACCESSOR_WITH_NAME(TYPE, MEMBER, NAME)				FULLY_CUSTOMIZED_ACCESSOR(TYPE, MEMBER, NAME, public, private,      , *,      , , &)
#define CONST_ACCESSOR_WITH_NAME(TYPE, MEMBER, NAME)			FULLY_CUSTOMIZED_ACCESSOR(TYPE, MEMBER, NAME, public, private, const,  , const, ,  )
#define CONST_REF_ACCESSOR_WITH_NAME(TYPE, MEMBER, NAME)		FULLY_CUSTOMIZED_ACCESSOR(TYPE, MEMBER, NAME, public, private, const, &, const, ,  )
#define CONST_PTR_ACCESSOR_WITH_NAME(TYPE, MEMBER, NAME)		FULLY_CUSTOMIZED_ACCESSOR(TYPE, MEMBER, NAME, public, private, const, *, const, , &)
#define SIMPLE_CONST_ACCESSOR_WITH_NAME(TYPE, MEMBER, NAME)		FULLY_CUSTOMIZED_ACCESSOR(TYPE, MEMBER, NAME, public, private,      ,  , const, ,  )

#define SAFE_ACCESSOR(TYPE, MEMBER)				SAFE_ACCESSOR_WITH_NAME(TYPE, MEMBER, MEMBER)
#define SAFE_REF_ACCESSOR(TYPE, MEMBER)			SAFE_REF_ACCESSOR_WITH_NAME(TYPE, MEMBER, MEMBER)
#define SAFE_PTR_ACCESSOR(TYPE, MEMBER)			SAFE_PTR_ACCESSOR_WITH_NAME(TYPE, MEMBER, MEMBER)
#define SAFE_CONST_ACCESSOR(TYPE, MEMBER)		SAFE_CONST_ACCESSOR_WITH_NAME(TYPE, MEMBER, MEMBER)
#define SAFE_CONST_REF_ACCESSOR(TYPE, MEMBER)	SAFE_CONST_REF_ACCESSOR_WITH_NAME(TYPE, MEMBER, MEMBER)
#define SAFE_CONST_PTR_ACCESSOR(TYPE, MEMBER)	SAFE_CONST_PTR_ACCESSOR_WITH_NAME(TYPE, MEMBER, MEMBER)

#define SAFE_ACCESSOR_WITH_NAME(TYPE, MEMBER, NAME)          \
	FULLY_CUSTOMIZED_ACCESSOR(TYPE, MEMBER, NAME, public, private,      ,  ,      , SAFETY_CHECK(m_##MEMBER),  )
#define SAFE_REF_ACCESSOR_WITH_NAME(TYPE, MEMBER, NAME)      \
	FULLY_CUSTOMIZED_ACCESSOR(TYPE, MEMBER, NAME, public, private,      , &,      , SAFETY_CHECK(m_##MEMBER),  )
#define SAFE_PTR_ACCESSOR_WITH_NAME(TYPE, MEMBER, NAME)       \
	FULLY_CUSTOMIZED_ACCESSOR(TYPE, MEMBER, NAME, public, private,      , *,      , SAFETY_CHECK(m_##MEMBER), &)
#define SAFE_CONST_ACCESSOR_WITH_NAME(TYPE, MEMBER, NAME)     \
	FULLY_CUSTOMIZED_ACCESSOR(TYPE, MEMBER, NAME, public, private, const,  , const, SAFETY_CHECK(m_##MEMBER),  )
#define SAFE_CONST_REF_ACCESSOR_WITH_NAME(TYPE, MEMBER, NAME) \
	FULLY_CUSTOMIZED_ACCESSOR(TYPE, MEMBER, NAME, public, private, const, &, const, SAFETY_CHECK(m_##MEMBER),  )
#define SAFE_CONST_PTR_ACCESSOR_WITH_NAME(TYPE, MEMBER, NAME) \
	FULLY_CUSTOMIZED_ACCESSOR(TYPE, MEMBER, NAME, public, private, const, *, const, SAFETY_CHECK(m_##MEMBER), &)

#define ACCESSOR_WITH_DOMAINS(TYPE, MEMBER, ACCESSOR_DOMAIN, EXTERNAL_DOMAIN) \
	FULLY_CUSTOMIZED_ACCESSOR(TYPE, MEMBER, MEMBER, ACCESSOR_DOMAIN, EXTERNAL_DOMAIN, , , , , )
#define SAFE_ACCESSOR_WITH_NAME_WITH_DOMAIN(TYPE, MEMBER, NAME, ACCESSOR_DOMAIN) \
	SAFE_ACCESSOR_WITH_NAME_WITH_DOMAINS(TYPE, MEMBER, NAME, ACCESSOR_DOMAIN, private)
#define SAFE_ACCESSOR_WITH_NAME_WITH_DOMAINS(TYPE, MEMBER, NAME, ACCESSOR_DOMAIN, EXTERNAL_DOMAIN) \
	FULLY_CUSTOMIZED_ACCESSOR(TYPE, MEMBER, NAME, ACCESSOR_DOMAIN, EXTERNAL_DOMAIN, , , , SAFETY_CHECK(m_##MEMBER), )

#define FULLY_CUSTOMIZED_ACCESSOR(TYPE,               \
                                  MEMBER,             \
                                  NAME,               \
                                  ACCESSOR_DOMAIN,    \
                                  EXTERNAL_DOMAIN,    \
                                  TYPE_CONSTNESS,     \
                                  TYPE_SUFFIX,        \
                                  ACCESSOR_CONSTNESS, \
                                  SAFETY_TEST,       \
                                  MEMBER_PREFIX)      \
	ACCESSOR_DOMAIN: \
		TYPE_CONSTNESS TYPE TYPE_SUFFIX NAME() ACCESSOR_CONSTNESS { SAFETY_TEST; return MEMBER_PREFIX m_##MEMBER; } \
	EXTERNAL_DOMAIN:

// Mutator helpers
#define MUTATOR(TYPE, MEMBER)					MUTATOR_WITH_NAME(TYPE, MEMBER, MUTATOR_NAME_FROM_MEMBER(MEMBER))
#define MUTATOR_REF_VALUE(TYPE, MEMBER)			MUTATOR_REF_VALUE_WITH_NAME(TYPE, MEMBER, MUTATOR_NAME_FROM_MEMBER(MEMBER))
#define MUTATOR_PTR_VALUE(TYPE_MEMBER)			MUTATOR_PTR_VALUE_WITH_NAME(TYPE, MEMBER, MUTATOR_NAME_FROM_MEMBER(MEMBER))
#define MUTATOR_CONST_VALUE(TYPE, MEMBER)		MUTATOR_CONST_VALUE_WITH_NAME(TYPE, MEMBER, MUTATOR_NAME_FROM_MEMBER(MEMBER))
#define MUTATOR_CONST_REF_VALUE(TYPE, MEMBER)	MUTATOR_CONST_REF_VALUE_WITH_NAME(TYPE, MEMBER, MUTATOR_NAME_FROM_MEMBER(MEMBER))
#define MUTATOR_CONST_PTR_VALUE(TYPE, MEMBER)	MUTATOR_CONST_PTR_VALUE_WITH_NAME(TYPE, MEMBER, MUTATOR_NAME_FROM_MEMBER(MEMBER))

#define MUTATOR_WITH_NAME(TYPE, MEMBER, NAME)					FULLY_CUSTOMIZED_MUTATOR(TYPE, MEMBER, NAME, public, private,      ,  ,  , )
#define MUTATOR_REF_VALUE_WITH_NAME(TYPE, MEMBER, NAME)			FULLY_CUSTOMIZED_MUTATOR(TYPE, MEMBER, NAME, public, private,      , &,  , )
#define MUTATOR_PTR_VALUE_WITH_NAME(TYPE, MEMBER, NAME)			FULLY_CUSTOMIZED_MUTATOR(TYPE, MEMBER, NAME, public, private,      , *, *, )
#define MUTATOR_CONST_VALUE_WITH_NAME(TYPE, MEMBER, NAME)		FULLY_CUSTOMIZED_MUTATOR(TYPE, MEMBER, NAME, public, private, const,  ,  , )
#define MUTATOR_CONST_REF_VALUE_WITH_NAME(TYPE, MEMBER, NAME)	FULLY_CUSTOMIZED_MUTATOR(TYPE, MEMBER, NAME, public, private, const, &,  , )
#define MUTATOR_CONST_PTR_VALUE_WITH_NAME(TYPE, MEMBER, NAME)	FULLY_CUSTOMIZED_MUTATOR(TYPE, MEMBER, NAME, public, private, const, *, *, )

#define SAFE_MUTATOR(TYPE, MEMBER)                                  \
	SAFE_MUTATOR_WITH_NAME(TYPE, MEMBER, MUTATOR_NAME_FROM_MEMBER(MEMBER))
#define SAFE_MUTATOR_PTR_VALUE(TYPE, MEMBER)                        \
	SAFE_MUTATOR_PTR_VALUE_WITH_NAME(TYPE, MEMBER, MUTATOR_NAME_FROM_MEMBER(MEMBER))
#define SAFE_MUTATOR_CONST_PTR_VALUE(TYPE, MEMBER)                 \
	SAFE_MUTATOR_CONST_PTR_VALUE_WITH_NAME(TYPE, MEMBER, MUTATOR_NAME_FROM_MEMBER(MEMBER))

#define SAFE_MUTATOR_WITH_NAME(TYPE, MEMBER, NAME)                 \
	FULLY_CUSTOMIZED_MUTATOR(TYPE, MEMBER, NAME, public, private,      ,  ,  , SAFETY_CHECK(MEMBER))
#define SAFE_MUTATOR_PTR_VALUE_WITH_NAME(TYPE, MEMBER, NAME)       \
	FULLY_CUSTOMIZED_MUTATOR(TYPE, MEMBER, NAME, public, private,      , *, *, SAFETY_CHECK(MEMBER))
#define SAFE_MUTATOR_CONST_PTR_VALUE_WITH_NAME(TYPE, MEMBER, NAME) \
	FULLY_CUSTOMIZED_MUTATOR(TYPE, MEMBER, NAME, public, private, const, *, *, SAFETY_CHECK(MEMBER))

#define MUTATOR_NAME_FROM_MEMBER(MEMBER)	set##MEMBER

#define FULLY_CUSTOMIZED_MUTATOR(TYPE,                 \
                                 MEMBER,               \
                                 NAME,                 \
                                 MUTATOR_DOMAIN,       \
                                 EXTERNAL_DOMAIN,      \
                                 VALUE_TYPE_CONSTNESS, \
                                 VALUE_TYPE_SUFFIX,    \
                                 VALUE_PREFIX,         \
                                 SAFETY_CHECK)         \
	MUTATOR_DOMAIN: \
		void NAME(VALUE_TYPE_CONSTNESS TYPE VALUE_TYPE_SUFFIX MEMBER) { SAFETY_CHECK; m_##MEMBER = VALUE_PREFIX MEMBER; } \
	EXTERNAL_DOMAIN:

// Constructor helpers
#define DECL_DEFAULT_CONSTRUCTOR(TYPE)		DECL_DEFAULT_CONSTRUCTOR_WITH_DOMAINS(TYPE, public, private)
#define IMPL_DEFAULT_CONSTRUCTOR(TYPE)		IMPL_DEFAULT_CONSTRUCTOR_WITH_DOMAINS(TYPE, public, private)
#define IMPL_DEFAULT_CONSTRUCTOR_WITH_PARENT_TYPE(TYPE, PARENT_TYPE) \
	IMPL_DEFAULT_CONSTRUCTOR_WITH_PARENT_TYPE_WITH_DOMAINS(TYPE, PARENT_TYPE, public, private)

#define DECL_DEFAULT_CONSTRUCTOR_WITH_DOMAINS(TYPE, CONSTRUCTOR_DOMAIN, EXTERNAL_DOMAIN)                               \
	FULLY_CUSTOMIZED_DEFAULT_CONSTRUCTOR(TYPE,              ,   ();, CONSTRUCTOR_DOMAIN, EXTERNAL_DOMAIN)
#define IMPL_DEFAULT_CONSTRUCTOR_WITH_DOMAINS(TYPE, CONSTRUCTOR_DOMAIN, EXTERNAL_DOMAIN)                               \
	FULLY_CUSTOMIZED_DEFAULT_CONSTRUCTOR(TYPE,              , (){} , CONSTRUCTOR_DOMAIN, EXTERNAL_DOMAIN)
#define IMPL_DEFAULT_CONSTRUCTOR_WITH_PARENT_TYPE_WITH_DOMAINS(TYPE, PARENT_TYPE, CONSTRUCTOR_DOMAIN, EXTERNAL_DOMAIN) \
	FULLY_CUSTOMIZED_DEFAULT_CONSTRUCTOR(TYPE, : PARENT_TYPE, (){} , CONSTRUCTOR_DOMAIN, EXTERNAL_DOMAIN)

#define FULLY_CUSTOMIZED_DEFAULT_CONSTRUCTOR(TYPE, PARENT_CALL, SUFFIX, CONSTRUCTOR_DOMAIN, EXTERNAL_DOMAIN) \
	CONSTRUCTOR_DOMAIN: \
		TYPE PARENT_CALL SUFFIX \
	EXTERNAL_DOMAIN:

// Destructor helpers
#define DECL_DESCTRUCTOR(TYPE)			DECL_DESTRUCTOR_WITH_DOMAINS(TYPE, public, private)
#define DECL_VIRTUAL_DESTRUCTOR(TYPE)	DECL_VIRTUAL_DESTRUCTOR_WITH_DOMAINS(TYPE, public, private)
#define IMPL_DESTRUCTOR(TYPE)			IMPL_DESTRUCTOR_WITH_DOMAINS(TYPE, public, private)
#define IMPL_VIRTUAL_DESTRUCTOR(TYPE)	IMPL_VIRTUAL_DESTRUCTOR_WITH_DOMAINS(TYPE, public, private)

#define DECL_DESTRUCTOR_WITH_DOMAINS(TYPE, DESTRUCTOR_DOMAIN, EXTERNAL_DOMAIN) \
	FULLY_CUSTOMIZED_DESTRUCTOR(TYPE,        ,   ();, DESTRUCTOR_DOMAIN, EXTERNAL_DOMAIN)
#define DECL_VIRTUAL_DESTRUCTOR_WITH_DOMAINS(TYPE, DESTRUCTOR_DOMAIN, EXTERNAL_DOMAIN) \
	FULLY_CUSTOMIZED_DESTRUCTOR(TYPE, virtual,   ();, DESTRUCTOR_DOMAIN, EXTERNAL_DOMAIN)
#define IMPL_DESTRUCTOR_WITH_DOMAINS(TYPE, DESTRUCTOR_DOMAIN, EXTERNAL_DOMAIN) \
	FULLY_CUSTOMIZED_DESTRUCTOR(TYPE,        , (){} , DESTRUCTOR_DOMAIN, EXTERNAL_DOMAIN)
#define IMPL_VIRTUAL_DESTRUCTOR_WITH_DOMAINS(TYPE, DESTRUCTOR_DOMAIN, EXTERNAL_DOMAIN) \
	FULLY_CUSTOMIZED_DESTRUCTOR(TYPE, virtual, (){} , DESTRUCTOR_DOMAIN, EXTERNAL_DOMAIN)

#define FULLY_CUSTOMIZED_DESTRUCTOR(TYPE, PREFIX, SUFFIX, DESTRUCTOR_DOMAIN, EXTERNAL_DOMAIN) \
	DESTRUCTOR_DOMAIN: \
		PREFIX ~ TYPE SUFFIX \
	EXTERNAL_DOMAIN:

#endif
