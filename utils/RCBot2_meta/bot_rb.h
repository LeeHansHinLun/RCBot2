#ifndef __RCBOT_RB_H__
#define __RCBOT_RB_H__
#include <vector>

class CBotOperator;

class CBotRule
{
public:
	CBotRule() = default;

private:
	std::vector<CBotOperator> m_Rules;
};

class CBotOperator
{
public:
	virtual ~CBotOperator() = default;

	CBotOperator ( const CBotFactOpertor& op ) : m_op(op)
	{		
	}

	virtual bool operate(const bool bVal, CBotOperator* pNext)
	{
		switch (m_op)
		{
		case OP_NONE:
			return bVal;
		case OP_PRE_NORM:
			return pNext->value();
			// Uncomment and implement these cases as needed
			// case OP_PRE_NOT:
			// case OP_AND:
			// case OP_OR:
			// case OP_AND_NOT:
			// case OP_OR_NOT:
		default:
			// Handle unexpected values of m_op
			return false; // or some other default behavior
		}
	}

	virtual bool value()
	{
		return true;
	}
private:
	CBotFactOperator m_op;
};
// for use with rule list
class CBotFact : public CBotOperator
{
public:
	CBotFact (const unsigned iFactId) : m_fid(iFactId)
	{
	}

	bool operate ( bVal, CBotOperator *pNext ) override
	{
		return m_bVal;
	}

	bool value() override
	{
		return m_bVal;
	}
private:
	unsigned m_fid;
	bool m_bVal;
};

typedef enum : std::uint8_t
{
	OP_NONE = 0,
	OP_PRE_NORM,
	OP_PRE_NOT,
	OP_AND,
	OP_OR,
	OP_AND_NOT,
	OP_OR_NOT
}CBotFactOperator;

#endif