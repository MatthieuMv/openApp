/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Operator
*/

#include <openApp/Containers/UMap.hpp>
#include <openApp/Types/Error.hpp>
#include <openApp/Language/Operator.hpp>

static const oA::UMap<oA::String, oA::Lang::OperatorModel> OperatorMap = {
    { "!",      { oA::Lang::Not                  }    },
    { "==",     { oA::Lang::Equal                }    },
    { "!=",     { oA::Lang::Different            }    },
    { ">",      { oA::Lang::Superior             }    },
    { ">=",     { oA::Lang::SuperiorEqual        }    },
    { "<",      { oA::Lang::Inferior             }    },
    { "<=",     { oA::Lang::InferiorEqual        }    },
    { "+",      { oA::Lang::Addition             }    },
    { "-",      { oA::Lang::Substraction         }    },
    { "*",      { oA::Lang::Multiplication       }    },
    { "/",      { oA::Lang::Division             }    },
    { "%",      { oA::Lang::Modulo               }    },
    { "=",      { oA::Lang::Assign               }    },
    { "+=",     { oA::Lang::AdditionAssign       }    },
    { "-=",     { oA::Lang::SubstractionAssign   }    },
    { "*=",     { oA::Lang::MultiplicationAssign }    },
    { "/=",     { oA::Lang::DivisionAssign       }    },
    { "%=",     { oA::Lang::ModuloAssign         }    },
    { "++",     { oA::Lang::PrefixIncrement      }    },
    { "++",     { oA::Lang::PrefixDecrement      }    },
    { "--",     { oA::Lang::SufixIncrement       }    },
    { "--",     { oA::Lang::SufixDecrement       }    }
};

bool oA::Lang::IsOperator(const oA::String &op)
{
    return OperatorMap.find(op) != OperatorMap.end();
}

const oA::Lang::OperatorModel &oA::Lang::GetOperator(const oA::String &op)
{
    auto it = OperatorMap.find(op);

    if (it == OperatorMap.end())
        throw AccessError("Operator", "Can't find operator @" + op + "@");
    return it->second;
}