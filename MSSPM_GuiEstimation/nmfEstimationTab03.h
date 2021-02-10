/**
 *
 * @file nmfEstimationTab03.h
 * @brief GUI definition for the nmfEstimation_Tab3 Competition Data class
 *
 * This file contains the GUI definition for the Competition Data page. This
 * page allows the user to enter/modify tables of data that correspond to
 * min/max competitive effects of predators on prey (i.e., of column Species
 * on row Species).
 *
 * @copyright
 * Public Domain Notice\n
 *
 * National Oceanic And Atmospheric Administration\n\n
 *
 * This software is a "United States Government Work" under the terms of the
 * United States Copyright Act.  It was written as part of the author's official
 * duties as a United States Government employee/contractor and thus cannot be copyrighted.
 * This software is freely available to the public for use. The National Oceanic
 * And Atmospheric Administration and the U.S. Government have not placed any
 * restriction on its use or reproduction.  Although all reasonable efforts have
 * been taken to ensure the accuracy and reliability of the software and data,
 * the National Oceanic And Atmospheric Administration and the U.S. Government
 * do not and cannot warrant the performance or results that may be obtained
 * by using this software or data. The National Oceanic And Atmospheric
 * Administration and the U.S. Government disclaim all warranties, express
 * or implied, including warranties of performance, merchantability or fitness
 * for any particular purpose.\n\n
 *
 * Please cite the author(s) in any work or product based on this material.
 */
#ifndef NMFESTIMATIONTAB3_H
#define NMFESTIMATIONTAB3_H

/**
 * @brief Competition Data
 *
 * These tables allow the user to enter and modify minimum and
 * maximum alpha and beta food Competition data.
 */
class nmfEstimation_Tab3: public QObject
{
    Q_OBJECT

private:
    nmfLogger*                       m_Logger;
    nmfDatabase*                     m_DatabasePtr;
    std::string                      m_ProjectDir;
    std::string                      m_ProjectSettingsConfig;
    QString                          m_CompetitionForm;
    QStringList                      m_SpeciesNames;
    QStringList                      m_GuildNames;
    std::vector<QStandardItemModel*> m_SModels;
    std::vector<QTableView*>         m_TableViews;
    std::vector<std::string>         m_AlphaTables;
    std::vector<std::string>         m_BetaSpeciesTables;
    std::vector<std::string>         m_BetaGuildsTables;
    std::vector<std::string>         m_BetaGuildsGuildsTables;

    QTabWidget*  Estimation_Tabs;
    QWidget*     Estimation_Tab3_Widget;
    QTableView*  Estimation_Tab3_CompetitionAlphaMinTV;
    QTableView*  Estimation_Tab3_CompetitionAlphaMaxTV;
    QTableView*  Estimation_Tab3_CompetitionBetaSpeciesMinTV;
    QTableView*  Estimation_Tab3_CompetitionBetaSpeciesMaxTV;
    QTableView*  Estimation_Tab3_CompetitionBetaGuildsMinTV;
    QTableView*  Estimation_Tab3_CompetitionBetaGuildsMaxTV;
    QLabel*      Estimation_Tab3_CompetitionAlphaMinLBL;
    QLabel*      Estimation_Tab3_CompetitionAlphaMaxLBL;
    QLabel*      Estimation_Tab3_CompetitionBetaSpeciesMinLBL;
    QLabel*      Estimation_Tab3_CompetitionBetaSpeciesMaxLBL;
    QLabel*      Estimation_Tab3_CompetitionBetaGuildsMinLBL;
    QLabel*      Estimation_Tab3_CompetitionBetaGuildsMaxLBL;
    QSplitter*   Estimation_Tab3_CompetitionMinSP;
    QSplitter*   Estimation_Tab3_CompetitionMaxSP;
    QPushButton* Estimation_Tab3_PrevPB;
    QPushButton* Estimation_Tab3_NextPB;
    QPushButton* Estimation_Tab3_SavePB;
    QPushButton* Estimation_Tab3_LoadPB;
    QPushButton* Estimation_Tab3_ImportPB;
    QPushButton* Estimation_Tab3_ExportPB;
    QCheckBox*   Estimation_Tab3_EstimateCB;

    QStringList getSpecies();
    QStringList getGuilds();
    void        readSettings();
    std::vector<std::string> getAllTableNames();
    bool isNoK();
    bool isMsProd();
    bool isAggProd();


public:
    /**
     * @brief nmfEstimation_Tab3 : class constructor for the Competition Parameters GUI page
     * @param tabs : the tab widget into which this Estimation tab will be placed
     * @param logger : pointer to the application logger
     * @param databasePtr : pointer to the application database
     * @param projectDir : the project directory
     */
    nmfEstimation_Tab3(QTabWidget*  tabs,
                       nmfLogger*   logger,
                       nmfDatabase* databasePtr,
                       std::string& projectDir);
    virtual ~nmfEstimation_Tab3();

    /**
     * @brief Clears the GUI's widgets
     */
    void clearWidgets();
    /**
     * @brief Loads all widgets for this GUI from database tables
     * @return Returns true if all data were loaded successfully
     */
    bool loadWidgets();
    void saveCSVFiles(std::vector<std::string>& allTableNames);
    void loadCSVFiles(std::vector<std::string>& allTableNames);

public Q_SLOTS:
    /**
     * @brief Callback invoked when the user clicks the Export button to save a .csv file
     */
    void callback_ExportPB();
    /**
     * @brief Callback invoked when the user clicks the Import button to load a .csv file
     */
    void callback_ImportPB();
    /**
     * @brief Callback invoked when the user clicks the Load button
     */
    void callback_LoadPB();
    /**
     * @brief Callback invoked when the user clicks the Save button
     */
    void callback_SavePB();
    /**
     * @brief Callback invoked when the user clicks the Previous Page button
     */
    void callback_PrevPB();
    /**
     * @brief Callback invoked when the user clicks the Next Page button
     */
    void callback_NextPB();
    /**
     * @brief Callback invoked when the user changes any of the Minimum Competitive Effects splitters
     * @param pos : position of the splitter
     * @param index : the index of the splitter changed
     */
    void callback_MinSplitterMoved(int pos, int index);
    /**
     * @brief Callback invoked when the user changes any of the Maximum Competitive Effects splitters
     * @param pos : position of the splitter
     * @param index : the index of the splitter changed
     */
    void callback_MaxSplitterMoved(int pos, int index);
    /**
     * @brief Callback invoked when the user updates the Competition Form in the Setup -> Model Setup page
     * @param competitionForm : the competition form selected by the user
     */
    void callback_CompetitionFormChanged(QString competitionForm);
    /**
     * @brief Callback invoked when the user toggles the Estimate checkbox
     * @param state : when set to Checked means that the minimum and maxumum estimated value limits are the same (effectively defining the parameter(s))
     */
    void callback_EstimateChecked(int state);
};

#endif // NMFESTIMATIONTAB3_H
