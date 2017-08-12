#ifndef MACROS_HPP
#define MACROS_HPP

// AppConfigs macros
#define GroupStart(Name) struct Name { Name() = delete;
#define Add(Type, Name, Value) static Type Name() { return Value; }
#define GroupEnd };

// QButton macros
#define AddButton(Name) private: QPushButton* Name; \
	                    private Q_SLOTS: void Name##Tapped();

#define ConstructButton(Name, Text) Name = new QPushButton(Text, this);\
	                                QObject::connect(Name, SIGNAL (released()), this, SLOT (Name##Tapped()));

#endif // MACROS_HPP
