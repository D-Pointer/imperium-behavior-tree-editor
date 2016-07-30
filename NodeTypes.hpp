#ifndef NODE_TYPES_HPP
#define NODE_TYPES_HPP

#include <QTreeWidgetItem>

enum NodeCategory {
    kAction,
    kComposite,
    kCondition,
    kDecorator,
    kRoot,
};

enum NodeType {
    // composites
    kRootType,
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

    // last unused item
    kUnusedMax
};

struct NodeData {
    NodeType m_type;
    NodeCategory m_category;
    QString m_typeText;
    QString m_categoryText;
    QString m_serializedId;
    bool m_leaf;
    bool m_hasValue;
};

static NodeData nodeData[] = {
    // composite
    { kRootType, kRoot, "Root", "Composite", "Root", false, false },
    { kSequence, kComposite, "Sequence", "Composite", "Sequence", false, false, },
    { kSelector, kComposite, "Selector", "Composite", "Selector", false, false, },

    // decorators
    { kSucceeder, kDecorator, "Succeeder", "Decorator", "Succeeder", false, false, },
    { kFailer, kDecorator, "Failer", "Decorator", "Failer", false, false, },
    { kLimiter, kDecorator, "Limiter", "Decorator", "Limiter", false, true },
    { kInverter, kDecorator, "Inverter", "Inverter", "Inverter", false, false },
    { kRepeater, kDecorator, "Repeater", "Decorator", "Repeater", false, true },
    { kRepeatUntilFail, kDecorator, "Repeat until fail", "Decorator", "RepeatUntilFail", false, true },
    { kRepeatUntilSucceed, kDecorator, "Repeat until succeed", "Decorator", "RepeatUntilSucceed", false, true },

    // unit conditions
    { kCanAssault, kCondition, "Can assault", "Condition", "CanAssault", true, false },
    { kCanRally, kCondition, "Can rally", "Condition", "CanRally", true, false },
    { kHasAmmo, kCondition, "Has ammo", "Condition", "HasAmmo", true, false },
    { kHasEnemiesInFieldOfFire, kCondition, "Has X enemies in field of fire", "Condition", "HasEnemiesInFof", true, true },
    { kHasEnemiesInRange, kCondition, "Has X enemies in range", "Condition", "HasEnemiesInRange", true, true },
    { kHasHq, kCondition, "Has HQ", "Condition", "HasHq", true, false },
    { kHasMission, kCondition, "Has mission", "Condition", "HasMission", true, false },
    { kHasTarget, kCondition, "Has target", "Condition", "HasTarget", true, false },
    { kIsColumnMode, kCondition, "In column mode", "Condition", "IsColumnMode", true, false },
    { kIsFormationMode, kCondition, "In formation mode", "Condition", "IsFormationMode", true, false },
    { kIsFullStrength, kCondition, "Is full strength", "Condition", "IsFullStrength", true, false },
    { kIsHalfStrength, kCondition, "Is half strength", "Condition", "IsHalfStrength", true, false },
    { kIsHq, kCondition, "Is HQ", "Condition", "IsHq", true, false },
    { kIsIndirectFireUnit, kCondition, "Is indirect fire unit", "Condition", "IsIndirectFireUnit", true, false },
    { kIsLowStrength, kCondition, "Is low strength", "Condition", "IsLowStrength", true, false },
    { kIsSupportUnit, kCondition, "Is support unit", "Condition", "IsSupportUnit", true, false },
    { kIsUnderFire, kCondition, "Is under fire", "Condition", "IsUnderFire", true, false },
    { kMorale, kCondition, "Morale over X", "Condition", "IsMmoraleOver", true, true },
    { kFatigue, kCondition, "Fatigue over X", "Condition", "IsFatigueOver", true, true },
    { kSeesEnemies, kCondition, "Sees X enemies", "Condition", "SeesEnemies", true, true },

    // global conditions
    { kAreAllObjectivesHeld, kCondition, "Are all objectives held", "Condition", "AreAllObjectivesHeld", true, false },
    { kAttackScenario, kCondition, "Is attack scenario", "Condition", "AttackScenario", true, false },
    { kBeginningOfGame, kCondition, "Is beginning of battle", "Condition", "BeginningOfBattle", true, false },
    { kDefendScenario, kCondition, "Is defend battle", "Condition", "DefendScenario", true, false },
    { kFirstTurn, kCondition, "Is first turn", "Condition", "FirstTurn", true, false },
    { kMeetingScenario, kCondition, "Is meeting engagement battle", "Condition", "MeetingScenario", true, false },

    // organization conditions
    { kIsHeadquarterAlive, kCondition, "Is headquarter alive", "Condition", "IsHeadquarterAlive", true, false },
    { kShouldAdvance, kCondition, "Should advance", "Condition", "ShouldAdvance", true, false },
    { kShouldHold, kCondition, "Should hold", "Condition", "ShouldHold", true, false },
    { kShouldTakeObjective, kCondition, "Should take objective", "Condition", "ShouldTakeObjective", true, false },

    // actions
    { kAssault, kAction, "Assault", "Action", "Assault", true, false },
    { kBombard, kAction, "Bombard", "Action", "Bombard", true, false },
    { kChangeMode, kAction, "Change mode", "Action", "ChangeMode", true, false },
    { kFaceNearestEnemy, kAction, "Face nearest enemy", "Action", "FaceNearestEnemy", true, false },
    { kFallBack, kAction, "Fall back", "Action", "FallBack", true, false },
    { kFire, kAction, "Fire", "Action", "Fire", true, false },
    { kHold, kAction, "Hold", "Action", "Hold", true, false },
    { kMoveForward, kAction, "Move forward", "Action", "MoveForward", true, false },
    { kRally, kAction, "Rally subordinates", "Action", "Rally", true, false },
    { kTakeObjective, kAction, "Take objective", "Action", "TakeObjective", true, false },

};

/**
 * Base class for all nodes.
 */
class Node : public QTreeWidgetItem {
public:

    Node (const NodeData & data, QTreeWidget *parent) : QTreeWidgetItem(parent), m_id(m_nextId++), m_data(data), m_value(0) {
        setup();
    }

    Node (const NodeData & data, int value) : m_id(m_nextId++), m_data(data), m_value(value) {
        setup();
    }

    Node (const NodeData & data, int value, QTreeWidgetItem *parent) : QTreeWidgetItem(parent), m_id(m_nextId++), m_data(data), m_value(value) {
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

    bool isRoot () const {
        return m_data.m_type == kRootType;
    }

    bool isComposite () const {
        return ! m_data.m_leaf;
    }

    bool isLeaf () const {
        return m_data.m_leaf;
    }

    bool hasValue () const {
        return m_data.m_hasValue;
    }

    int getValue () const {
        return m_value;
    }

    void setValue (int value) {
        m_value = value;
    }

    void setData (const NodeData & data) {
        m_data = data;
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
            type.replace( "X", QString::number(m_value) );
            setText( 0, type );
        }

        setText( 1, m_data.m_categoryText );

        switch ( m_data.m_category ) {
        case kAction:
            setForeground( 0, QBrush( Qt::darkRed) );
            setForeground( 1, QBrush( Qt::darkRed) );
            break;
        case kComposite:
            setForeground( 0, QBrush( Qt::darkBlue) );
            setForeground( 1, QBrush( Qt::darkBlue) );
            break;
        case kCondition:
            setForeground( 0, QBrush( Qt::darkGreen) );
            setForeground( 1, QBrush( Qt::darkGreen) );
            break;
        case kDecorator:
            setForeground( 0, QBrush( Qt::darkGray) );
            setForeground( 1, QBrush( Qt::darkGray) );
            break;
        case kRoot:
            break;
        }

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
    int m_value;
};


#endif // NODE_TYPES_HPP
