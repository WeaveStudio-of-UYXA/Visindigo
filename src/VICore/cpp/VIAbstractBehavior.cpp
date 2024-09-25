#include "../VIAbstractBehavior.h"

/*! 
	\class VIAbstractBehavior
	\brief VIAbstractBehavior是所有需要按刻更新的内容的基类
	\inmodule VICore
	\since Visindigo 2.0.0

	此类是所有需要按刻更新的内容的基类，所有继承此类的类都需要实现onStart()和onEnd()函数。
*/

/*! \fn VIAbstractBehavior::VIAbstractBehavior(VISuper* parent)
	\brief 构造函数
	\since Visindigo 2.0.0
	\a parent 父对象
*/
def_init VIAbstractBehavior::VIAbstractBehavior(QString name, VISuper* parent)
	:VIObject(parent)
{
}
/*! \fn void VIAbstractBehavior::onStart()
	\brief 开始函数
	\since Visindigo 2.0.0

	此函数在开始时调用
*/
void VIAbstractBehavior::onStart()
{
}

/*! \fn void VIAbstractBehavior::onEnd()
	\brief 结束函数
	\since Visindigo 2.0.0

	此函数在结束时调用
*/
void VIAbstractBehavior::onEnd()
{
}
