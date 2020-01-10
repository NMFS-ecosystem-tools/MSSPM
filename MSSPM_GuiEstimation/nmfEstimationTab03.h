/** @file nmfEstimationTab03.h
 * @brief GUI definition for the nmfEstimation_Tab3 Competition Data class
 *
 * This file contains the GUI definition for the Competition Data page. This
 * page allows the user to enter/modify tables of data that correspond to
 * min/max competitive effects of predators on prey (i.e., of column Species
 * on row Species).
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
    QCheckBox*   Estimation_Tab3_EstimateCB;

    QStringList getSpecies();
    QStringList getGuilds();
    void        readSettings();

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

public Q_SLOTS:
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
