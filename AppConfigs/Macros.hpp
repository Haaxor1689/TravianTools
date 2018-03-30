#ifndef MACROS_HPP
#define MACROS_HPP

// AppConfigs macros
#define GroupStart(Name) struct Name { Name() = delete;
#define Add(Type, Name, Value) \
	    static Type& Name() { static Type data(Value); return data; }

#define AddConst(Type, Name, Value) \
	public: \
	    static Type Name() { return Value; } \

#define GroupEnd };

// QButton macros
#define AddButton(Name) private: QPushButton* Name; \
	                    private Q_SLOTS: void Name##Tapped();

// Connect macros
#define ConnectPair(Sender, Reciever, Method) \
	QObject::connect(Sender, SIGNAL(Method), Reciever, SLOT(Method));

#endif // MACROS_HPP
