#ifndef DATASETCOMBOBOX_H
#define DATASETCOMBOBOX_H

#include <QComboBox>

class DataSetComboBox : public QComboBox {
public:
  DataSetComboBox(const QString& nodeName, QWidget* parent = nullptr);
  virtual ~DataSetComboBox() override;

  void read();

private slots:
  void setData(const QString& value);

private:
  QString m_nodeName;
};

#endif // DATASETCOMBOBOX_H
