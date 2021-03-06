// -*- C++ -*-
#ifndef _ResearchWnd_h_
#define _ResearchWnd_h_

#include "CUIWnd.h"

#include <GG/ListBox.h>

class QueueListBox;
class Tech;
class TechTreeWnd;
class ProductionInfoPanel;

/** Contains a TechTreeWnd, some stats on the empire-wide research queue, and the queue itself. */
class ResearchWnd : public GG::Wnd {
public:
    /** \name Structors */ //@{
    ResearchWnd(GG::X w, GG::Y h);
    ~ResearchWnd();
    //@}

    /** \name Mutators */ //@{
    virtual void SizeMove(const GG::Pt& ul, const GG::Pt& lr);

    void    Refresh();
    void    Reset();
    void    Update();
    void    CenterOnTech(const std::string& tech_name);
    void    ShowTech(const std::string& tech_name);
    void    QueueItemMoved(GG::ListBox::Row* row, std::size_t position);
    void    Sanitize();

    void    Render();

    /** Enables, or disables if \a enable is false, issuing orders via this ResearchWnd. */
    void    EnableOrderIssuing(bool enable = true);
    //@}

private:
    void    DoLayout();
    void    ResearchQueueChangedSlot();
    void    UpdateQueue();
    void    UpdateInfoPanel();     ///< Updates research summary at top left of production screen, and signals that the empire's minerals research pool has changed (propegates to the mapwnd to update indicator)
    void    DeleteQueueItem(GG::ListBox::iterator it);
    void    AddTechsToQueueSlot(const std::vector<std::string>& tech_vec, int pos = -1);
    void    QueueItemClickedSlot(GG::ListBox::iterator it, const GG::Pt& pt);
    void    QueueItemDoubleClickedSlot(GG::ListBox::iterator it);

    ProductionInfoPanel*        m_research_info_panel;
    QueueListBox*               m_queue_lb;
    TechTreeWnd*                m_tech_tree_wnd;
    bool                        m_enabled;

    boost::signals2::connection m_empire_connection;
};

#endif // _ResearchWnd_h_
