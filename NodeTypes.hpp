#ifndef NODE_TYPES_HPP
#define NODE_TYPES_HPP

#include <QTreeWidgetItem>

enum NodeCategory {
    kAction,
    kComposite,
    kCondition,
    kDecorator,
    kInclude,
    kRoot,
};

enum NodeType {
    // composites
    kSequence,
    kSelector,

    // decorators
    kSucceeder,
    kFailer,
    kLimiter,
    kInverter,
    kRepeater,
    kRepeatUntilFail,
    kRepeatUntilSucceed,

    // unit conditions
    kCanAssault,
    kCanRally,
    kHasAmmo,
    kHasEnemiesInFieldOfFire,
    kHasEnemiesInRange,
    kHasHq,
    kHasMission,
    kHasTarget,
    kIsColumnMode,
    kIsFormationMode,
    kIsFullStrength,
    kIsHalfStrength,
    kIsHq,
    kIsIndirectFireUnit,
    kIsLowStrength,
    kIsSupportUnit,
    kIsUnderFire,
    kMorale,
    kFatigue,
    kSeesEnemies,
    kAreAllObjectivesHeld,

    // global conditions
    kAttackScenario,
    kBeginningOfGame,
    kDefendScenario,
    kFirstTurn,
    kMeetingScenario,

    // organization conditions
    kIsHeadquarterAlive,
    kShouldAdvance,
    kShouldHold,
    kShouldTakeObjective,

    kAssault,
    kBombard,
    kChangeMode,
    kFaceNearestEnemy,
    kFallBack,
    kFire,
    kHold,
    kMoveForward,
    kRally,
    kTakeObjective,

    // include
    kIncludeSubtree,

    // unit conditions
    kIsInfantry,
    kIsCavalry,
    kIsArtillery,
    kIsIdle,

    // composite
    kIf,

    // last unused item
    kUnusedMax
};

struct NodeData {
    NodeType m_type;
    NodeCategory m_category;
    QString m_typeText;
    QString m_categoryText;
    QString m_serializedId;
    int m_maxChildren;
    bool m_hasValue;
};

static NodeData nodeData[] = {
    // composite
    { kSequence, kComposite, "Sequence", "Composite", "Sequence", INT32_MAX, false, },
    { kSelector, kComposite, "Selector", "Composite", "Selector", INT32_MAX, false, },

    // decorators
    { kSucceeder, kDecorator, "Succeeder", "Decorator", "Succeeder", 1, false, },
    { kFailer, kDecorator, "Failer", "Decorator", "Failer", 1, false, },
    { kLimiter, kDecorator, "Limiter", "Decorator", "Limiter", 1, true },
    { kInverter, kDecorator, "Inverter", "Inverter", "Inverter", 1, false },
    { kRepeater, kDecorator, "Repeater", "Decorator", "Repeater", 1, true },
    { kRepeatUntilFail, kDecorator, "Repeat until fail", "Decorator", "RepeatUntilFail", 1, true },
    { kRepeatUntilSucceed, kDecorator, "Repeat until succeed", "Decorator", "RepeatUntilSucceed", 1, true },

    // unit conditions
    { kCanAssault, kCondition, "Can assault", "Condition", "CanAssault", 0, false },
    { kCanRally, kCondition, "Can rally", "Condition", "CanRally", 0, false },
    { kHasAmmo, kCondition, "Has ammo", "Condition", "HasAmmo", 0, false },
    { kHasEnemiesInFieldOfFire, kCondition, "Has X enemies in field of fire", "Condition", "HasEnemiesInFieldOfFire", 0, true },
    { kHasEnemiesInRange, kCondition, "Has X enemies in range", "Condition", "HasEnemiesInRange", 0, true },
    { kHasHq, kCondition, "Has HQ", "Condition", "HasHq", 0, false },
    { kHasMission, kCondition, "Has mission", "Condition", "HasMission", 0, false },
    { kHasTarget, kCondition, "Has target", "Condition", "HasTarget", 0, false },
    { kIsColumnMode, kCondition, "In column mode", "Condition", "IsColumnMode", 0, false },
    { kIsFormationMode, kCondition, "In formation mode", "Condition", "IsFormationMode", 0, false },
    { kIsFullStrength, kCondition, "Is full strength", "Condition", "IsFullStrength", 0, false },
    { kIsHalfStrength, kCondition, "Is half strength", "Condition", "IsHalfStrength", 0, false },
    { kIsHq, kCondition, "Is HQ", "Condition", "IsHq", 0, false },
    { kIsIndirectFireUnit, kCondition, "Is indirect fire unit", "Condition", "IsIndirectFireUnit", 0, false },
    { kIsLowStrength, kCondition, "Is low strength", "Condition", "IsLowStrength", 0, false },
    { kIsSupportUnit, kCondition, "Is support unit", "Condition", "IsSupportUnit", 0, false },
    { kIsUnderFire, kCondition, "Is under fire", "Condition", "IsUnderFire", 0, false },
    { kMorale, kCondition, "Morale over X", "Condition", "IsMmoraleOver", 0, true },
    { kFatigue, kCondition, "Fatigue over X", "Condition", "IsFatigueOver", 0, true },
    { kSeesEnemies, kCondition, "Sees X enemies", "Condition", "SeesEnemies", 0, true },

    // global conditions
    { kAreAllObjectivesHeld, kCondition, "Are all objectives held", "Condition", "AreAllObjectivesHeld", 0, false },
    { kAttackScenario, kCondition, "Is attack scenario", "Condition", "AttackScenario", 0, false },
    { kBeginningOfGame, kCondition, "Is beginning of battle", "Condition", "BeginningOfBattle", 0, false },
    { kDefendScenario, kCondition, "Is defend battle", "Condition", "DefendScenario", 0, false },
    { kFirstTurn, kCondition, "Is first turn", "Condition", "FirstTurn", 0, false },
    { kMeetingScenario, kCondition, "Is meeting engagement battle", "Condition", "MeetingScenario", 0, false },

    // organization conditions
    { kIsHeadquarterAlive, kCondition, "Is headquarter alive", "Condition", "IsHeadquarterAlive", 0, false },
    { kShouldAdvance, kCondition, "Should advance", "Condition", "ShouldAdvance", 0, false },
    { kShouldHold, kCondition, "Should hold", "Condition", "ShouldHold", 0, false },
    { kShouldTakeObjective, kCondition, "Should take objective", "Condition", "ShouldTakeObjective", 0, false },

    // actions
    { kAssault, kAction, "Assault", "Action", "Assault", 0, false },
    { kBombard, kAction, "Bombard", "Action", "Bombard", 0, false },
    { kChangeMode, kAction, "Change mode", "Action", "ChangeMode", 0, false },
    { kFaceNearestEnemy, kAction, "Face nearest enemy", "Action", "FaceNearestEnemy", 0, false },
    { kFallBack, kAction, "Fall back", "Action", "FallBack", 0, false },
    { kFire, kAction, "Fire", "Action", "Fire", 0, false },
    { kHold, kAction, "Hold", "Action", "Hold", 0, false },
    { kMoveForward, kAction, "Move forward", "Action", "MoveForward", 0, false },
    { kRally, kAction, "Rally subordinates", "Action", "Rally", 0, false },
    { kTakeObjective, kAction, "Take objective", "Action", "TakeObjective", 0, false },

     // include
    { kIncludeSubtree, kInclude, "Include subtree X", "Include", "Include", 0, true },

    // unit conditions
    { kIsInfantry, kCondition, "Is infantry unit", "Condition", "IsInfantryUnit", 0, false },
    { kIsCavalry, kCondition, "Is cavalry unit", "Condition", "IsCavalryUnit", 0, false },
    { kIsArtillery, kCondition, "Is artillery unit", "Condition", "IsArtilleryUnit", 0, false },
    { kIsIdle, kCondition, "Is idle", "Condition", "IsIdle", 0, false },

    // composite
    { kIf, kComposite, "If", "Composite", "If", 3, false },
};

/**
 * Base class for all nodes.
 */
class Node : public QTreeWidgetItem {
public:

    Node (const NodeData & data, QTreeWidget *parent) : QTreeWidgetItem(parent), m_id(m_nextId++), m_data(data), m_value(""), m_comment("") {
        setup();
    }

    Node (const NodeData & data, const QString & value, QTreeWidgetItem *parent=nullptr) : QTreeWidgetItem(parent), m_id(m_nextId++), m_data(data), m_value(value), m_comment("") {
        setup();
    }

    int getId () const {
        return m_id;
    }

    QString getTypeText () const {
        return m_data.m_typeText;
    }

    NodeCategory getCategory () const {
        return m_data.m_category;
    }

    NodeType getType () const {
        return m_data.m_type;
    }

    QString getSerializationId () const {
        return m_data.m_serializedId;
    }

    int getMaxChildCount () const {
        return m_data.m_maxChildren;
    }

    bool isRoot () const {
        return m_data.m_type == kSequence && parent() == nullptr;
    }

    bool isComposite () const {
        return m_data.m_category == kComposite;
    }

    bool isLeaf () const {
        return m_data.m_maxChildren;
    }

    bool hasValue () const {
        return m_data.m_hasValue;
    }

    const QString & getValue () const {
        return m_value;
    }

    void setValue (const QString & value) {
        m_value = value;
    }

    void setNodeData (const NodeData & data) {
        m_data = data;
    }

    const QString & getComment () const {
        return m_comment;
    }

    void setComment (const QString & comment) {
        m_comment = comment;
    }

    void setup () {
        if ( ! m_data.m_hasValue ) {
            setText( 0, m_data.m_typeText );
        }
        else if ( ! m_data.m_typeText.contains( "X")) {
            setText( 0, m_data.m_typeText );
        }
        else {
            QString type = m_data.m_typeText;
            type.replace( "X", m_value );
            setText( 0, type );
        }

        setText( 1, m_comment );

        switch ( m_data.m_category ) {
        case kAction:
            setForeground( 0, QBrush( Qt::darkRed) );
            break;
        case kComposite:
            setForeground( 0, QBrush( Qt::darkBlue) );
            break;
        case kCondition:
            setForeground( 0, QBrush( Qt::darkCyan) );
            break;
        case kDecorator:
            setForeground( 0, QBrush( Qt::darkGray) );
            break;
        case kInclude:
            setForeground( 0, QBrush( Qt::darkMagenta) );
            break;
        case kRoot:
            break;
        }

        // all comments are dark green and italic
        setForeground( 1, QBrush( Qt::darkGreen) );
        QFont currentFont = font( 2 );
        setFont( 1, QFont( currentFont.family(), currentFont.pointSize(), currentFont.weight(), true) );

        if ( isComposite() ) {
            setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDropEnabled | Qt::ItemIsDragEnabled );
        }
        else {
            setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled );
        }
    }


private:

    int m_id;
    static int m_nextId;
    NodeData m_data;
    QString m_value;
    QString m_comment;
};

#endif // NODE_TYPES_HPP
