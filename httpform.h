#ifndef HTTPFORM_H
#define HTTPFORM_H

#include <QWidget>
#include "baseform.h"
#include "ui_httpform.h"

namespace Ui {
class httpform;
}

class httpform : public BaseForm
{
    Q_OBJECT
protected:
    virtual bool initForm();
    virtual bool initHotkeys();
    virtual void initConfig();
    virtual void saveConfig();
    virtual void send(const QString& data, const QString& dir);
public:
    explicit httpform(QWidget *parent = nullptr);
    ~httpform();


private:
    Ui::httpform *ui;
};

#endif // HTTPFORM_H
