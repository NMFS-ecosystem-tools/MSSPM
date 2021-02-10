#include "nmfEstimationTab03.h"
#include "nmfConstantsMSSPM.h"
#include "nmfUtils.h"
#include "nmfUtilsQt.h"
#include "nmfConstants.h"

nmfEstimation_Tab3::nmfEstimation_Tab3(QTabWidget*  tabs,
                                       nmfLogger*   logger,
                                       nmfDatabase* databasePtr,
                                       std::string& projectDir)
{
    int NumSpecies;
    int NumGuilds;
    int NumGuildTableViews   = 0;
    int NumSpeciesTableViews = 0;
    QUiLoader loader;

    m_Logger      = logger;
    m_DatabasePtr = databasePtr;
    m_SpeciesNames.clear();
    m_GuildNames.clear();
    m_CompetitionForm.clear();
    m_SModels.clear();

    readSettings();

    m_Logger->logMsg(nmfConstants::Normal,"nmfEstimation_Tab3::nmfEstimation_Tab3");

    Estimation_Tabs = tabs;

    m_AlphaTables.push_back("CompetitionAlphaMin");
    m_AlphaTables.push_back("CompetitionAlphaMax");
    m_BetaSpeciesTables.push_back("CompetitionBetaSpeciesMin");
    m_BetaSpeciesTables.push_back("CompetitionBetaSpeciesMax");
    m_BetaGuildsTables.push_back("CompetitionBetaGuildsMin");
    m_BetaGuildsTables.push_back("CompetitionBetaGuildsMax");
    m_BetaGuildsGuildsTables.push_back("CompetitionBetaGuildsGuildsMin");
    m_BetaGuildsGuildsTables.push_back("CompetitionBetaGuildsGuildsMax");

    m_ProjectDir = projectDir;

    // Load ui as a widget from disk
    QFile file(":/forms/Estimation/Estimation_Tab03.ui");
    file.open(QFile::ReadOnly);
    Estimation_Tab3_Widget = loader.load(&file,Estimation_Tabs);
    file.close();

    // Add the loaded widget as the new tabbed page
    Estimation_Tabs->addTab(Estimation_Tab3_Widget, tr("3. Competition Parameters"));

    Estimation_Tab3_CompetitionAlphaMinTV        = Estimation_Tabs->findChild<QTableView  *>("Estimation_Tab3_CompetitionAlphaMinTV");
    Estimation_Tab3_CompetitionAlphaMaxTV        = Estimation_Tabs->findChild<QTableView  *>("Estimation_Tab3_CompetitionAlphaMaxTV");
    Estimation_Tab3_CompetitionBetaSpeciesMinTV  = Estimation_Tabs->findChild<QTableView  *>("Estimation_Tab3_CompetitionBetaSpeciesMinTV");
    Estimation_Tab3_CompetitionBetaSpeciesMaxTV  = Estimation_Tabs->findChild<QTableView  *>("Estimation_Tab3_CompetitionBetaSpeciesMaxTV");
    Estimation_Tab3_CompetitionBetaGuildsMinTV   = Estimation_Tabs->findChild<QTableView  *>("Estimation_Tab3_CompetitionBetaGuildsMinTV");
    Estimation_Tab3_CompetitionBetaGuildsMaxTV   = Estimation_Tabs->findChild<QTableView  *>("Estimation_Tab3_CompetitionBetaGuildsMaxTV");
    Estimation_Tab3_CompetitionAlphaMinLBL       = Estimation_Tabs->findChild<QLabel      *>("Estimation_Tab3_CompetitionAlphaMinLBL");
    Estimation_Tab3_CompetitionAlphaMaxLBL       = Estimation_Tabs->findChild<QLabel      *>("Estimation_Tab3_CompetitionAlphaMaxLBL");
    Estimation_Tab3_CompetitionBetaSpeciesMinLBL = Estimation_Tabs->findChild<QLabel      *>("Estimation_Tab3_CompetitionBetaSpeciesMinLBL");
    Estimation_Tab3_CompetitionBetaSpeciesMaxLBL = Estimation_Tabs->findChild<QLabel      *>("Estimation_Tab3_CompetitionBetaSpeciesMaxLBL");
    Estimation_Tab3_CompetitionBetaGuildsMinLBL  = Estimation_Tabs->findChild<QLabel      *>("Estimation_Tab3_CompetitionBetaGuildsMinLBL");
    Estimation_Tab3_CompetitionBetaGuildsMaxLBL  = Estimation_Tabs->findChild<QLabel      *>("Estimation_Tab3_CompetitionBetaGuildsMaxLBL");
    Estimation_Tab3_CompetitionMinSP             = Estimation_Tabs->findChild<QSplitter   *>("Estimation_Tab3_CompetitionMinSP");
    Estimation_Tab3_CompetitionMaxSP             = Estimation_Tabs->findChild<QSplitter   *>("Estimation_Tab3_CompetitionMaxSP");
    Estimation_Tab3_PrevPB                       = Estimation_Tabs->findChild<QPushButton *>("Estimation_Tab3_PrevPB");
    Estimation_Tab3_NextPB                       = Estimation_Tabs->findChild<QPushButton *>("Estimation_Tab3_NextPB");
    Estimation_Tab3_LoadPB                       = Estimation_Tabs->findChild<QPushButton *>("Estimation_Tab3_LoadPB");
    Estimation_Tab3_SavePB                       = Estimation_Tabs->findChild<QPushButton *>("Estimation_Tab3_SavePB");
    Estimation_Tab3_ImportPB                     = Estimation_Tabs->findChild<QPushButton *>("Estimation_Tab3_ImportPB");
    Estimation_Tab3_ExportPB                     = Estimation_Tabs->findChild<QPushButton *>("Estimation_Tab3_ExportPB");
    Estimation_Tab3_EstimateCB                   = Estimation_Tabs->findChild<QCheckBox   *>("Estimation_Tab3_EstimateCB");

    Estimation_Tab3_CompetitionAlphaMinTV->setToolTip("Minimum Value for Alpha Coeff of Column Species on Row Species");
    Estimation_Tab3_CompetitionAlphaMaxTV->setToolTip("Maximum Value for Alpha Coeff of Column Species on Row Species");
    Estimation_Tab3_CompetitionBetaSpeciesMinTV->setToolTip("Minimum Value for Beta (Species) Coeff of Column Species on Row Species");
    Estimation_Tab3_CompetitionBetaSpeciesMaxTV->setToolTip("Maximum Value for Beta (Species) Coeff of Column Species on Row Species");
    Estimation_Tab3_CompetitionBetaGuildsMinTV->setToolTip("Minimum Value for Beta (Guilds) Coeff of Column Guilds on Row Species");
    Estimation_Tab3_CompetitionBetaGuildsMaxTV->setToolTip("Maximum Value for Beta (Guilds) Coeff of Column Guilds on Row Species");

    connect(Estimation_Tab3_PrevPB,   SIGNAL(clicked()),
            this,                     SLOT(callback_PrevPB()));
    connect(Estimation_Tab3_NextPB,   SIGNAL(clicked()),
            this,                     SLOT(callback_NextPB()));
    connect(Estimation_Tab3_LoadPB,   SIGNAL(clicked()),
            this,                     SLOT(callback_LoadPB()));
    connect(Estimation_Tab3_SavePB,   SIGNAL(clicked()),
            this,                     SLOT(callback_SavePB()));
    connect(Estimation_Tab3_ImportPB, SIGNAL(clicked()),
            this,                     SLOT(callback_ImportPB()));
    connect(Estimation_Tab3_ExportPB, SIGNAL(clicked()),
            this,                     SLOT(callback_ExportPB()));
    connect(Estimation_Tab3_CompetitionMinSP, SIGNAL(splitterMoved(int,int)),
            this,                             SLOT(callback_MinSplitterMoved(int,int)));
    connect(Estimation_Tab3_CompetitionMaxSP, SIGNAL(splitterMoved(int,int)),
            this,                             SLOT(callback_MaxSplitterMoved(int,int)));
    connect(Estimation_Tab3_EstimateCB,       SIGNAL(stateChanged(int)),
            this,                             SLOT(callback_EstimateChecked(int)));

    Estimation_Tab3_PrevPB->setText("\u25C1--");
    Estimation_Tab3_NextPB->setText("--\u25B7");

    m_TableViews.clear();
    m_TableViews.push_back(Estimation_Tab3_CompetitionAlphaMinTV);
    m_TableViews.push_back(Estimation_Tab3_CompetitionAlphaMaxTV);
    m_TableViews.push_back(Estimation_Tab3_CompetitionBetaSpeciesMinTV);
    m_TableViews.push_back(Estimation_Tab3_CompetitionBetaSpeciesMaxTV);
    NumSpeciesTableViews = m_TableViews.size();
    m_TableViews.push_back(Estimation_Tab3_CompetitionBetaGuildsMinTV);
    m_TableViews.push_back(Estimation_Tab3_CompetitionBetaGuildsMaxTV);
    NumGuildTableViews   = m_TableViews.size() - NumSpeciesTableViews;

    NumSpecies = getSpecies().size();
    NumGuilds  = getGuilds().size();
    QStandardItemModel* smodel;
    for (int i=0; i<NumSpeciesTableViews; ++i) {
        smodel = new QStandardItemModel(NumSpecies, NumSpecies);
        m_SModels.push_back(smodel);
        m_TableViews[i]->setModel(smodel);
    }
    for (int i=0; i<NumGuildTableViews; ++i) {
        smodel = new QStandardItemModel(NumSpecies, NumGuilds);
        m_SModels.push_back(smodel);
        m_TableViews[NumSpeciesTableViews+i]->setModel(smodel);
    }

}


nmfEstimation_Tab3::~nmfEstimation_Tab3()
{

}

void
nmfEstimation_Tab3::clearWidgets()
{
    nmfUtilsQt::clearTableView(
        {Estimation_Tab3_CompetitionAlphaMinTV,
         Estimation_Tab3_CompetitionAlphaMaxTV,
         Estimation_Tab3_CompetitionBetaSpeciesMinTV,
         Estimation_Tab3_CompetitionBetaSpeciesMaxTV,
         Estimation_Tab3_CompetitionBetaGuildsMinTV,
         Estimation_Tab3_CompetitionBetaGuildsMaxTV});
}

QStringList
nmfEstimation_Tab3::getSpecies()
{
    QStringList speciesList;
    std::vector<std::string> species;

    m_DatabasePtr->getAllSpecies(m_Logger,species);
    for (std::string aSpecies : species) {
        speciesList << QString::fromStdString(aSpecies);
    }

    return speciesList;
}

QStringList
nmfEstimation_Tab3::getGuilds()
{
    QStringList guildsList;
    std::vector<std::string> guilds;

    m_DatabasePtr->getAllGuilds(m_Logger,guilds);
    for (std::string aGuild : guilds) {
        guildsList << QString::fromStdString(aGuild);
    }

    return guildsList;
}

void
nmfEstimation_Tab3::readSettings()
{
    QSettings* settings = nmfUtilsQt::createSettings(nmfConstantsMSSPM::SettingsDirWindows,"MSSPM");

    settings->beginGroup("Settings");
    m_ProjectSettingsConfig = settings->value("Name","").toString().toStdString();
    settings->endGroup();

    settings->beginGroup("SetupTab");
    m_ProjectDir = settings->value("ProjectDir","").toString().toStdString();
    settings->endGroup();

    delete settings;
}

void
nmfEstimation_Tab3::callback_PrevPB()
{
    int prevPage = Estimation_Tabs->currentIndex()-1;
    Estimation_Tabs->setCurrentIndex(prevPage);
}

void
nmfEstimation_Tab3::callback_NextPB()
{
    int nextPage = Estimation_Tabs->currentIndex()+1;
    Estimation_Tabs->setCurrentIndex(nextPage);
}

void
nmfEstimation_Tab3::callback_LoadPB()
{
    if (loadWidgets()) {
        QMessageBox::information(Estimation_Tabs, "Competition Load",
                                 "\nCompetition table(s) successfully loaded.\n",
                                 QMessageBox::Ok);
    }
}

void
nmfEstimation_Tab3::callback_MinSplitterMoved(int pos, int index)
{
   Estimation_Tab3_CompetitionMaxSP->setSizes(Estimation_Tab3_CompetitionMinSP->sizes());
}

void
nmfEstimation_Tab3::callback_MaxSplitterMoved(int pos, int index)
{
   Estimation_Tab3_CompetitionMinSP->setSizes(Estimation_Tab3_CompetitionMaxSP->sizes());
}

void
nmfEstimation_Tab3::callback_CompetitionFormChanged(QString competitionForm)
{
    QList<int> minSizeList;
    QList<int> maxSizeList;
    int numSections  = Estimation_Tab3_CompetitionMinSP->sizes().size();
    int defaultWidth = Estimation_Tab3_CompetitionMinSP->width()/3;

    m_CompetitionForm = competitionForm;
    for (int i=0; i<numSections; ++i) {
        minSizeList.push_back(defaultWidth);
        maxSizeList.push_back(defaultWidth);
    }
    Estimation_Tab3_CompetitionMinSP->setSizes(minSizeList);
    Estimation_Tab3_CompetitionMaxSP->setSizes(maxSizeList);

    Estimation_Tab3_CompetitionAlphaMinTV->setEnabled(false);
    Estimation_Tab3_CompetitionAlphaMaxTV->setEnabled(false);
    Estimation_Tab3_CompetitionBetaSpeciesMinTV->setEnabled(false);
    Estimation_Tab3_CompetitionBetaSpeciesMaxTV->setEnabled(false);
    Estimation_Tab3_CompetitionBetaGuildsMinTV->setEnabled(false);
    Estimation_Tab3_CompetitionBetaGuildsMaxTV->setEnabled(false);
    Estimation_Tab3_CompetitionAlphaMinLBL->setEnabled(false);
    Estimation_Tab3_CompetitionAlphaMaxLBL->setEnabled(false);
    Estimation_Tab3_CompetitionBetaSpeciesMinLBL->setEnabled(false);
    Estimation_Tab3_CompetitionBetaSpeciesMaxLBL->setEnabled(false);
    Estimation_Tab3_CompetitionBetaGuildsMinLBL->setEnabled(false);
    Estimation_Tab3_CompetitionBetaGuildsMaxLBL->setEnabled(false);

    if (m_CompetitionForm == "NO_K") {
        Estimation_Tab3_CompetitionAlphaMinTV->setEnabled(true);
        Estimation_Tab3_CompetitionAlphaMaxTV->setEnabled(true);
        Estimation_Tab3_CompetitionAlphaMinLBL->setEnabled(true);
        Estimation_Tab3_CompetitionAlphaMaxLBL->setEnabled(true);
        for (int i=1; i<numSections; ++i) {
            minSizeList[i] = 0;
            maxSizeList[i] = 0;
        }
    } else if (m_CompetitionForm == "AGG-PROD") {
        Estimation_Tab3_CompetitionBetaGuildsMinTV->setEnabled(true);
        Estimation_Tab3_CompetitionBetaGuildsMaxTV->setEnabled(true);
        Estimation_Tab3_CompetitionBetaGuildsMinLBL->setEnabled(true);
        Estimation_Tab3_CompetitionBetaGuildsMaxLBL->setEnabled(true);
        for (int i=0; i<numSections-1; ++i) {
            minSizeList[i] = 0;
            maxSizeList[i] = 0;
        }
    } else if (m_CompetitionForm == "MS-PROD") {
        Estimation_Tab3_CompetitionBetaSpeciesMinTV->setEnabled(true);
        Estimation_Tab3_CompetitionBetaSpeciesMaxTV->setEnabled(true);
        Estimation_Tab3_CompetitionBetaSpeciesMinLBL->setEnabled(true);
        Estimation_Tab3_CompetitionBetaSpeciesMaxLBL->setEnabled(true);
        Estimation_Tab3_CompetitionBetaGuildsMinTV->setEnabled(true);
        Estimation_Tab3_CompetitionBetaGuildsMaxTV->setEnabled(true);
        Estimation_Tab3_CompetitionBetaGuildsMinLBL->setEnabled(true);
        Estimation_Tab3_CompetitionBetaGuildsMaxLBL->setEnabled(true);
        minSizeList[0] = 0;
        maxSizeList[0] = 0;
    }
    Estimation_Tab3_CompetitionMinSP->setSizes(minSizeList);
    Estimation_Tab3_CompetitionMaxSP->setSizes(maxSizeList);
}

void
nmfEstimation_Tab3::callback_ImportPB()
{
    QString selectMsg;
    QString inputDataPath = QDir(QString::fromStdString(m_ProjectDir)).filePath(QString::fromStdString(nmfConstantsMSSPM::InputDataDir));
    std::vector<std::string> allTableNames = getAllTableNames();
    int numTables = allTableNames.size();

    // Load default CSV files
    std::string msg = "\nLoad default Competition .csv files?";
    QMessageBox::StandardButton reply = QMessageBox::question(Estimation_Tabs, tr("Default Competition CSV Files"),
                                                              tr(msg.c_str()),
                                                              QMessageBox::No|QMessageBox::Yes|QMessageBox::Cancel,
                                                              QMessageBox::Yes);
    if (reply == QMessageBox::Cancel) {
        return;
    } else if (reply == QMessageBox::Yes) {
        loadCSVFiles(allTableNames);
    } else {
        QString filePrefix = (isNoK()) ? "CompetitionAlphaMin" :
                                         (isMsProd()) ? "CompetitionBetaSpeciesMin" :
                                                        "CompetitionBetaGuildsGuildsMin";
        // if no, raise browser and have user select appropriate file.
        selectMsg = "Select "+filePrefix+"*.csv file";
        QString filename = QFileDialog::getOpenFileName(
                    Estimation_Tabs,
                    QObject::tr(selectMsg.toLatin1()), inputDataPath,
                    QObject::tr("Data Files (*.csv)"));
        QFileInfo fi(filename);
        QString base = fi.baseName();
        QStringList parts = base.split(filePrefix);
        if (parts.size() == 2) {
            QString tag = parts[1];
            for (int i=0; i<numTables; ++i) {
                allTableNames[i] += tag.toStdString();
            }
            loadCSVFiles(allTableNames);            
        } else {

            QMessageBox::information(Estimation_Tabs, "Competition CSV Import",
                                     "\nPlease make sure to select the filename that begins with:\n" + filePrefix + "\n",
                                     QMessageBox::Ok);
        }
    }
}

void
nmfEstimation_Tab3::loadCSVFiles(std::vector<std::string>& allTableNames)
{
    bool loadOK;
    QString errorMsg;
    QString tableName;
    QString inputDataPath = QDir(QString::fromStdString(m_ProjectDir)).filePath(QString::fromStdString(nmfConstantsMSSPM::InputDataDir));

    int tableNum = 0;
    for (QTableView* tv : m_TableViews) {
        tableName = QString::fromStdString(allTableNames[tableNum]);
        tableName = QDir(inputDataPath).filePath(tableName+".csv");
        loadOK = nmfUtilsQt::loadTimeSeries(
                    Estimation_Tabs, tv, inputDataPath, tableName,
                    nmfConstantsMSSPM::FirstLineNotReadOnly,
                    errorMsg);
        if (! loadOK) {
            m_Logger->logMsg(nmfConstants::Error,errorMsg.toStdString());
        }
        ++tableNum;
    }
}

std::vector<std::string>
nmfEstimation_Tab3::getAllTableNames()
{
    std::vector<std::string> allTableNames;
    std::vector<std::vector<std::string> > tableList;

    if (m_CompetitionForm == "MS-PROD") {
        tableList = {m_AlphaTables,m_BetaSpeciesTables,m_BetaGuildsTables};
    } else {
        tableList = {m_AlphaTables,m_BetaSpeciesTables,m_BetaGuildsGuildsTables};
    }
    for (std::vector<std::string> tableVec : tableList)
    {
        for (std::string tableName : tableVec) {
            allTableNames.push_back(tableName);
        }
    }

    return allTableNames;
}

void
nmfEstimation_Tab3::callback_SavePB()
{
    bool systemFound = false;
    int  inc         = -1;
    int  tableInc    = -1;
    int  numSpecies  = m_SpeciesNames.size();
    int  numGuilds   = m_GuildNames.size();
    std::vector<std::string> allTableNames = getAllTableNames();
    int numTables = allTableNames.size();
    std::string cmd;
    std::string errorMsg;
    std::string value;
    std::string Algorithm,Minimizer,ObjectiveCriterion;
    std::string Scaling,CompetitionForm;
    QString msg;
    QModelIndex index;
    boost::numeric::ublas::matrix<double> MinMax[numTables];
    std::vector<std::string> GuildTables;
    std::string VariableNames;
    std::string speciesName;
    std::string guildName;

    readSettings();

    // Find Algorithm type
    systemFound = m_DatabasePtr->getAlgorithmIdentifiers(
                Estimation_Tabs,m_Logger,m_ProjectSettingsConfig,
                Algorithm,Minimizer,ObjectiveCriterion,
                Scaling,CompetitionForm,nmfConstantsMSSPM::DontShowPopupError);
    if (! systemFound) {
        m_Logger->logMsg(nmfConstants::Error,"nmfEstimation_Tab3::callback_SavePB: Couldn't find any System algorithms");
        return;
    }
    if (m_SModels.size() == 0) {
        m_Logger->logMsg(nmfConstants::Warning,"nmfEstimation_Tab3::callback_SavePB m_SModels is empty.");
        return;
    }

    Estimation_Tabs->setCursor(Qt::WaitCursor);

    for (unsigned i=0; i<m_AlphaTables.size(); ++i) {
        nmfUtils::initialize(MinMax[++inc], numSpecies, numSpecies);
    }
    for (unsigned i=0; i<m_BetaSpeciesTables.size(); ++i) {
        nmfUtils::initialize(MinMax[++inc], numSpecies, numSpecies);
    }
    if (m_CompetitionForm == "MS-PROD") {
        for (unsigned i=0; i<m_BetaGuildsTables.size(); ++i) {
            nmfUtils::initialize(MinMax[++inc], numSpecies, numGuilds);
        }
    } else {
        for (unsigned i=0; i<m_BetaGuildsGuildsTables.size(); ++i) {
            nmfUtils::initialize(MinMax[++inc], numGuilds,  numGuilds);
        }
    }

    // Alpha
    if (m_CompetitionForm == "NO_K") {
        if (! nmfUtilsQt::allMaxCellsGreaterThanMinCells(m_SModels[tableInc+1],m_SModels[tableInc+2])) {
            m_Logger->logMsg(nmfConstants::Error,"[Error 1] nmfEstimation_Tab3::callback_SavePB: At least one Max cell less than a Min cell: " + errorMsg);
            QMessageBox::critical(Estimation_Tabs, "Error",
                                 "\nError: There's at least one Max cell less than a Min cell. Please check tables.\n",
                                 QMessageBox::Ok);
            Estimation_Tabs->setCursor(Qt::ArrowCursor);
            return;
        }
        for (unsigned int k=0; k<m_AlphaTables.size(); ++k) {
            ++tableInc;
            cmd = "DELETE FROM " + m_AlphaTables[tableInc] + " WHERE SystemName = '" + m_ProjectSettingsConfig + "'";
            errorMsg = m_DatabasePtr->nmfUpdateDatabase(cmd);
            if (nmfUtilsQt::isAnError(errorMsg)) {
                m_Logger->logMsg(nmfConstants::Error,"[Error 2] nmfEstimation_Tab3::callback_SavePB: DELETE error: " + errorMsg);
                m_Logger->logMsg(nmfConstants::Error,"cmd: " + cmd);
                QMessageBox::warning(Estimation_Tabs, "Error",
                                     "\nError in Save command.  Couldn't delete all records from Competition table.\n",
                                     QMessageBox::Ok);
                Estimation_Tabs->setCursor(Qt::ArrowCursor);
                return;
            }

            cmd = "INSERT INTO " + m_AlphaTables[tableInc] + " (SystemName,SpeciesA,SpeciesB,Value) VALUES ";
            for (int i=0; i<m_SModels[tableInc]->rowCount(); ++i) {
                for (int j=0; j<m_SModels[tableInc]->columnCount(); ++ j) {
                    index = m_SModels[tableInc]->index(i,j);
                    value = index.data().toString().toStdString();
                    MinMax[tableInc](i,j) = index.data().toDouble();
                    cmd += "('" + m_ProjectSettingsConfig + "','" + m_SpeciesNames[i].toStdString() + "','" +
                            m_SpeciesNames[j].toStdString() + "', " + value + "),";
                }
            }
            cmd = cmd.substr(0,cmd.size()-1);
            errorMsg = m_DatabasePtr->nmfUpdateDatabase(cmd);
            if (nmfUtilsQt::isAnError(errorMsg)) {
                m_Logger->logMsg(nmfConstants::Error,"nmfEstimation_Tab3::callback_SavePB(1): Write table error: " + errorMsg);
                m_Logger->logMsg(nmfConstants::Error,"cmd: " + cmd);
                QMessageBox::warning(Estimation_Tabs, "Error",
                                     "\nError in Save command.  Check that all cells are populated.\n",
                                     QMessageBox::Ok);
                Estimation_Tabs->setCursor(Qt::ArrowCursor);
                return;
            }
        }

        // Check if user is running a Genetic Algorithm that if there's a value in MinMax[1], there's a
        // non-zero value in MinMax[0].
        for (int i=0; i<m_SModels[0]->rowCount(); ++i) {
            for (int j=0; j<m_SModels[0]->columnCount(); ++j) {
                if ((Algorithm == "Genetic Algorithm") &&
                        (MinMax[1](i,j) > 0) && (MinMax[0](i,j) <= 0)) {
                    msg  = "\nWarning: All non-zero Max values must have a non-zero Min value.\n\n";
                    msg += "Please modify current table as needed.\n";
                    QMessageBox::warning(Estimation_Tabs, "Warning Min/Max Data",msg,
                                         QMessageBox::Ok);
                    Estimation_Tabs->setCursor(Qt::ArrowCursor);
                    return;
                }
            }
        }
    } else {
        tableInc += m_AlphaTables.size();
    }

    // Beta Species
    if (m_CompetitionForm == "MS-PROD") {
        if (! nmfUtilsQt::allMaxCellsGreaterThanMinCells(m_SModels[tableInc+1],m_SModels[tableInc+2])) {
            m_Logger->logMsg(nmfConstants::Error,"[Error 3] nmfEstimation_Tab3::callback_SavePB: At least one Max cell less than a Min cell: " + errorMsg);
            QMessageBox::critical(Estimation_Tabs, "Error",
                                 "\nError: There's at least one Max cell less than a Min cell. Please check tables.\n",
                                 QMessageBox::Ok);
            Estimation_Tabs->setCursor(Qt::ArrowCursor);
            return;
        }
        for (unsigned int k=0; k<m_BetaSpeciesTables.size(); ++k) {
            ++tableInc;
            cmd = "DELETE FROM " + m_BetaSpeciesTables[k] + " WHERE SystemName = '" + m_ProjectSettingsConfig + "'";
            errorMsg = m_DatabasePtr->nmfUpdateDatabase(cmd);
            if (nmfUtilsQt::isAnError(errorMsg)) {
                m_Logger->logMsg(nmfConstants::Error,"[Error 4] nmfEstimation_Tab3::callback_SavePB: DELETE error: " + errorMsg);
                m_Logger->logMsg(nmfConstants::Error,"cmd: " + cmd);
                QMessageBox::warning(Estimation_Tabs, "Error",
                                     "\nError in Save command.  Couldn't delete all records from Competition table.\n",
                                     QMessageBox::Ok);
                Estimation_Tabs->setCursor(Qt::ArrowCursor);
                return;
            }

            cmd = "INSERT INTO " + m_BetaSpeciesTables[k] + " (SystemName,SpeciesA,SpeciesB,Value) VALUES ";
            for (int i=0; i<m_SModels[tableInc]->rowCount(); ++i) {
                for (int j=0; j<m_SModels[tableInc]->columnCount(); ++ j) {
                    index = m_SModels[tableInc]->index(i,j);
                    value = index.data().toString().toStdString();
                    MinMax[tableInc](i,j) = index.data().toDouble();
                    cmd += "('" + m_ProjectSettingsConfig + "','" + m_SpeciesNames[i].toStdString() + "','" +
                            m_SpeciesNames[j].toStdString() + "', " + value + "),";
                }
            }
            cmd = cmd.substr(0,cmd.size()-1);
            errorMsg = m_DatabasePtr->nmfUpdateDatabase(cmd);
            if (nmfUtilsQt::isAnError(errorMsg)) {
                m_Logger->logMsg(nmfConstants::Error,"nmfEstimation_Tab3::callback_SavePB(2): Write table error: " + errorMsg);
                m_Logger->logMsg(nmfConstants::Error,"cmd: " + cmd);
                QMessageBox::warning(Estimation_Tabs, "Error",
                                     "\nError in Save command.  Check that all cells are populated.\n",
                                     QMessageBox::Ok);
                Estimation_Tabs->setCursor(Qt::ArrowCursor);
                return;
            }
        }
    } else {
        tableInc += m_BetaSpeciesTables.size();
    }

    // Beta Guilds
    if ((m_CompetitionForm == "MS-PROD") || (m_CompetitionForm == "AGG-PROD")) {
        if (! nmfUtilsQt::allMaxCellsGreaterThanMinCells(m_SModels[tableInc+1],m_SModels[tableInc+2])) {
            m_Logger->logMsg(nmfConstants::Error,"[Error 5] nmfEstimation_Tab3::callback_SavePB: At least one Max cell less than a Min cell: " + errorMsg);
            QMessageBox::critical(Estimation_Tabs, "Error",
                                 "\nError: There's at least one Max cell less than a Min cell. Please check tables.\n",
                                 QMessageBox::Ok);
            Estimation_Tabs->setCursor(Qt::ArrowCursor);
            return;
        }
        if (m_CompetitionForm == "MS-PROD") {
            GuildTables   = m_BetaGuildsTables;
            VariableNames = "Guild,SpeName";
        } else {
            GuildTables   = m_BetaGuildsGuildsTables;
            VariableNames = "GuildA,GuildB";
        }
        for (unsigned int k=0; k<GuildTables.size(); ++k) {
            ++tableInc;
            cmd = "DELETE FROM " + GuildTables[k] + " WHERE SystemName = '" + m_ProjectSettingsConfig + "'";
            errorMsg = m_DatabasePtr->nmfUpdateDatabase(cmd);
            if (nmfUtilsQt::isAnError(errorMsg)) {
                m_Logger->logMsg(nmfConstants::Error,"[Error 6] nmfEstimation_Tab3::callback_SavePB: DELETE error: " + errorMsg);
                m_Logger->logMsg(nmfConstants::Error,"cmd: " + cmd);
                QMessageBox::warning(Estimation_Tabs, "Error",
                                     "\nError in Save command.  Couldn't delete all records from Competition table.\n",
                                     QMessageBox::Ok);
                Estimation_Tabs->setCursor(Qt::ArrowCursor);
                return;
            }

            cmd = "INSERT INTO " + GuildTables[k] + " (SystemName,"+VariableNames+",Value) VALUES ";
            for (int i=0; i<m_SModels[tableInc]->rowCount(); ++i) {
                for (int j=0; j<m_SModels[tableInc]->columnCount(); ++ j) {
                    index = m_SModels[tableInc]->index(i,j);
                    value = index.data().toString().toStdString();
                    MinMax[tableInc](i,j) = index.data().toDouble();
                    if (m_CompetitionForm == "MS-PROD") {
                        cmd += "('" + m_ProjectSettingsConfig   + "','" +
                                m_SpeciesNames[i].toStdString() + "','" +
                                m_GuildNames[j].toStdString()   + "', " + value + "),";
                    } else {
                        cmd += "('" + m_ProjectSettingsConfig + "','" +
                                m_GuildNames[i].toStdString() + "','" +
                                m_GuildNames[j].toStdString() + "', " + value + "),";
                    }
                }
            }
            cmd = cmd.substr(0,cmd.size()-1);
            errorMsg = m_DatabasePtr->nmfUpdateDatabase(cmd);
            if (nmfUtilsQt::isAnError(errorMsg)) {
                m_Logger->logMsg(nmfConstants::Error,"nmfEstimation_Tab3::callback_SavePB(3): Write table error: " + errorMsg);
                m_Logger->logMsg(nmfConstants::Error,"cmd: " + cmd);
                QMessageBox::warning(Estimation_Tabs, "Error",
                                     "\nError in Save command.  Check that all cells are populated.\n",
                                     QMessageBox::Ok);
                Estimation_Tabs->setCursor(Qt::ArrowCursor);
                return;
            }
        }
    }

    QMessageBox::information(Estimation_Tabs, "Competition Min/Max Updated",
                             "\nCompetition Min/Max tables have been successfully updated.\n",
                             QMessageBox::Ok);

    // Reload widgets so column sizing will re-adjust
    loadWidgets();

    Estimation_Tabs->setCursor(Qt::ArrowCursor);
}

void
nmfEstimation_Tab3::callback_ExportPB()
{
    std::vector<std::string> allTableNames = getAllTableNames();
    int numTables = allTableNames.size();

    // Save time series data to a .csv file
    if (int(allTableNames.size()) == numTables) {
        std::string msg = "\nOK to use default file names for Competition .csv files and overwrite any previous files?";
        QMessageBox::StandardButton reply = QMessageBox::question(Estimation_Tabs, tr("Default Competition CSV Files"),
                                                                  tr(msg.c_str()),
                                                                  QMessageBox::No|QMessageBox::Yes|QMessageBox::Cancel,
                                                                  QMessageBox::Yes);
        if (reply == QMessageBox::Cancel) {
            return;
        } else if (reply == QMessageBox::Yes) {
            saveCSVFiles(allTableNames);
        } else {
            bool ok;
            QString tag = QInputDialog::getText(Estimation_Tabs, tr("Competition Files"),
                                                 tr("Enter Competition CSV filename version tag (omit any '_'): "), QLineEdit::Normal,
                                                 "", &ok);
            if (ok && !tag.isEmpty()) {
                 for (int i=0; i<numTables; ++i) {
                     allTableNames[i] += "_"+tag.toStdString();
                 }
                 saveCSVFiles(allTableNames);
            } else if (tag.isEmpty()) {
                QMessageBox::warning(Estimation_Tabs, "Tag Error",
                                     "\nError: Please enter a valid (i.e., non-blank) tag.\n",
                                     QMessageBox::Ok);
            }
        }
    } else {
        m_Logger->logMsg(nmfConstants::Error,"Error: allTablesNames different size than m_TableViews");
    }
}

void
nmfEstimation_Tab3::saveCSVFiles(
        std::vector<std::string>& allTableNames)
{
    bool okSave;
    bool atLeastOneError = false;
    int tableNum = 0;
    QString tableNameWithPath;
    QString savedFilenames;
    QString inputDataPath = QDir(QString::fromStdString(m_ProjectDir)).filePath(QString::fromStdString(nmfConstantsMSSPM::InputDataDir));

    for (QTableView* tv : m_TableViews) {
        tableNameWithPath = QDir(inputDataPath).filePath(QString::fromStdString(allTableNames[tableNum]));
        QStandardItemModel* smodel = qobject_cast<QStandardItemModel*>(tv->model());
        okSave = nmfUtilsQt::saveTimeSeries(Estimation_Tabs,smodel,inputDataPath,tableNameWithPath);
        savedFilenames += tableNameWithPath+"\n";
        if (!okSave) {
            atLeastOneError = true;
        }
        ++tableNum;
    }
    if (atLeastOneError) {
        QMessageBox::information(Estimation_Tabs, "Competition Files Saved",
                                 "\nAll Competition CSV files have not been saved. Please check for valid filenames.\n",
                                 QMessageBox::Ok);
    } else {
        QMessageBox::information(Estimation_Tabs, "Competition Files Saved",
                                 "\nCompetition CSV files have been successfully saved as:\n\n"+savedFilenames,
                                 QMessageBox::Ok);
    }

}


void
nmfEstimation_Tab3::callback_EstimateChecked(int state)
{
    int numRows;
    int numCols;
    QModelIndex indexMin;
    QModelIndex indexMax;
    QStandardItemModel* smodelMin;
    QStandardItemModel* smodelMax;

    if (state != Qt::Checked) {
        for (unsigned k=0; k<m_TableViews.size(); k += 2) {
            smodelMin = qobject_cast<QStandardItemModel*>(m_TableViews[k]->model());
            smodelMax = qobject_cast<QStandardItemModel*>(m_TableViews[k+1]->model());
            numRows   = m_TableViews[k]->model()->rowCount();
            numCols   = m_TableViews[k]->model()->columnCount();
            for (int i=0; i<numRows; ++i) {
                for (int j=0; j<numCols;++j) {
                    indexMin = smodelMin->index(i,j);
                    indexMax = smodelMax->index(i,j);
                    smodelMax->setData(indexMax,smodelMin->data(indexMin));
                }
            }
        }
    } else {
        loadWidgets();
    }
}

bool
nmfEstimation_Tab3::isNoK()
{
    return (m_CompetitionForm == "NO_K");
}

bool
nmfEstimation_Tab3::isAggProd()
{
    return (m_CompetitionForm == "AGG-PROD");
}

bool
nmfEstimation_Tab3::isMsProd()
{
    return (m_CompetitionForm == "MS-PROD");
}

bool
nmfEstimation_Tab3::loadWidgets()
{
    m_Logger->logMsg(nmfConstants::Normal,"nmfEstimation_Tab3::loadWidgets()");

    int m;
    int NumSpecies;
    int NumGuilds;
    int NumCoeffs;
    int tableInc = -1;
    std::vector<std::string> fields;
    std::map<std::string, std::vector<std::string> > dataMap;
    std::string queryStr;
    std::string competitionForm = "";
    QStandardItem*      item;
    QStandardItemModel* smodel;
    std::vector<std::string> GuildTables;
    std::string VariableNames;
    std::string speciesName;
    std::string guildName;

    m_SpeciesNames.clear();
    m_GuildNames.clear();

    readSettings();

    if (m_ProjectSettingsConfig.empty()) {
        m_Logger->logMsg(nmfConstants::Warning,"nmfEstimation_Tab3::loadWidgets: No System found.");
    }

    clearWidgets();

    // Get Species and Guild names
    m_SpeciesNames = getSpecies();
    m_GuildNames   = getGuilds();
    NumSpecies     = m_SpeciesNames.size();
    NumGuilds      = m_GuildNames.size();

    // Get competitionForm
    fields    = {"WithinGuildCompetitionForm"};
    queryStr  = "SELECT WithinGuildCompetitionForm FROM Systems WHERE ";
    queryStr += " SystemName = '" + m_ProjectSettingsConfig + "'";
    dataMap   = m_DatabasePtr->nmfQueryDatabase(queryStr, fields);
    if (dataMap["WithinGuildCompetitionForm"].size() > 0) {
        competitionForm = dataMap["WithinGuildCompetitionForm"][0];
    }

    for (unsigned int k=0; k<m_AlphaTables.size(); ++k) {
        ++tableInc;
        fields    = {"SystemName","SpeciesA","SpeciesB","Value"};
        queryStr  = "SELECT SystemName,SpeciesA,SpeciesB,Value FROM " + m_AlphaTables[k] +
                    " WHERE SystemName = '" + m_ProjectSettingsConfig + "'";
        dataMap   = m_DatabasePtr->nmfQueryDatabase(queryStr, fields);
        NumCoeffs = dataMap["SpeciesA"].size();
        m = 0;
        for (int i=0; i<NumSpecies; ++i) {
            for (int j=0; j<NumSpecies; ++j) {
                if ((NumCoeffs > 0) && (m < NumCoeffs))
                    item = new QStandardItem(QString::fromStdString(dataMap["Value"][m++]));
                else
                    item = new QStandardItem("");
                item->setTextAlignment(Qt::AlignCenter);
                m_SModels[tableInc]->setItem(i, j, item);
            }
        }
        m_SModels[tableInc]->setVerticalHeaderLabels(m_SpeciesNames);
        m_SModels[tableInc]->setHorizontalHeaderLabels(m_SpeciesNames);
        m_TableViews[tableInc]->resizeColumnsToContents();
    }

    for (unsigned int k=0; k<m_BetaSpeciesTables.size(); ++k) {
        ++tableInc;
        NumCoeffs = 0;
        if (! m_ProjectSettingsConfig.empty()) {
            fields    = {"SystemName","SpeciesA","SpeciesB","Value"};
            queryStr  = "SELECT SystemName,SpeciesA,SpeciesB,Value FROM " + m_BetaSpeciesTables[k] +
                        " WHERE SystemName = '" + m_ProjectSettingsConfig + "'";
            dataMap   = m_DatabasePtr->nmfQueryDatabase(queryStr, fields);
            NumCoeffs = dataMap["SpeciesA"].size();
        }
        m = 0;
        for (int i=0; i<NumSpecies; ++i) {
            for (int j=0; j<NumSpecies; ++j) {
                if ((NumCoeffs > 0) && (m < NumCoeffs))
                    item = new QStandardItem(QString::fromStdString(dataMap["Value"][m++]));
                else
                    item = new QStandardItem("");
                item->setTextAlignment(Qt::AlignCenter);
                m_SModels[tableInc]->setItem(i, j, item);
            }
        }
        m_SModels[tableInc]->setVerticalHeaderLabels(m_SpeciesNames);
        m_SModels[tableInc]->setHorizontalHeaderLabels(m_SpeciesNames);
        m_TableViews[tableInc]->resizeColumnsToContents();
    }
    int NumSpeciesOrGuilds = (isAggProd()) ? NumGuilds : NumSpecies;

    if (isMsProd()) {
        GuildTables   = m_BetaGuildsTables;
        VariableNames = "Guild,SpeName";
    } else if (isAggProd()) {
        GuildTables   = m_BetaGuildsGuildsTables;
        VariableNames = "GuildA,GuildB";
    }

    for (unsigned int k=0; k<GuildTables.size(); ++k) {
        ++tableInc;
        if (isMsProd()) {
           smodel = new QStandardItemModel(NumSpecies, NumGuilds);
           m_SModels[tableInc] = smodel;
           m_TableViews[tableInc]->setModel(smodel);
        } else if (isAggProd()) {
            smodel = new QStandardItemModel(NumGuilds, NumGuilds);
            m_SModels[tableInc] = smodel;
            m_TableViews[tableInc]->setModel(smodel);
        }
        NumCoeffs = 0;
        if (! m_ProjectSettingsConfig.empty()) {
            fields    = {"SystemName","SpeName","Guild","Value"};
            queryStr  = "SELECT SystemName,"+VariableNames+",Value FROM " + GuildTables[k] +
                        " WHERE SystemName = '" + m_ProjectSettingsConfig + "'";
            dataMap   = m_DatabasePtr->nmfQueryDatabase(queryStr, fields);
            NumCoeffs = dataMap["SpeName"].size();
        }
        m = 0;
        for (int i=0; i<NumSpeciesOrGuilds; ++i) {
            for (int j=0; j<NumGuilds; ++j) {
                if ((NumCoeffs > 0) && (m < NumCoeffs))
                    item = new QStandardItem(QString::fromStdString(dataMap["Value"][m++]));
                else
                    item = new QStandardItem("");
                item->setTextAlignment(Qt::AlignCenter);
                m_SModels[tableInc]->setItem(i, j, item);
            }
        }
        if (isAggProd()) {
            m_SModels[tableInc]->setVerticalHeaderLabels(m_GuildNames);
        } else if (isMsProd()) {
            m_SModels[tableInc]->setVerticalHeaderLabels(m_SpeciesNames);
        }
        m_SModels[tableInc]->setHorizontalHeaderLabels(m_GuildNames);
        m_TableViews[tableInc]->resizeColumnsToContents();
    }

    // Set enable-ness on widgets
    callback_CompetitionFormChanged(QString::fromStdString(competitionForm));

    return true;
}

