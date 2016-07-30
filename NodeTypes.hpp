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
    int m_value;
};

static NodeData nodeData[] = {
    // composite
    { kRootType, kRoot, "Root", "Composite", "Root", false, false, 0 },
    { kSequence, kComposite, "Sequence", "Composite", "Sequence", false, false, 0, },
    { kSelector, kComposite, "Selector", "Composite", "Selector", false, false, 0, },

    // decorators
    { kSucceeder, kDecorator, "Succeeder", "Decorator", "Succeeder", false, false, 0, },
    { kFailer, kDecorator, "Failer", "Decorator", "Failer", false, false, 0, },
    { kLimiter, kDecorator, "Limiter", "Decorator", "Limiter", false, true, 0 },
    { kInverter, kDecorator, "Inverter", "Inverter", "Inverter", false, false, 0 },
    { kRepeater, kDecorator, "Repeater", "Decorator", "Repeater", false, true, 0 },
    { kRepeatUntilFail, kDecorator, "Repeat until fail", "Decorator", "RepeatUntilFail", false, true, 0 },
    { kRepeatUntilSucceed, kDecorator, "Repeat until succeed", "Decorator", "RepeatUntilSucceed", false, true, 0 },

    // unit conditions
    { kCanAssault, kCondition, "Can assault", "Condition", "CanAssault", true, false, 0 },
    { kCanRally, kCondition, "Can rally", "Condition", "CanRally", true, false, 0 },
    { kHasAmmo, kCondition, "Has ammo", "Condition", "HasAmmo", true, false, 0 },
    { kHasEnemiesInFieldOfFire, kCondition, "Has X enemies in field of fire", "Condition", "HasEnemiesInFof", true, true, 0 },
    { kHasEnemiesInRange, kCondition, "Has X enemies in range", "Condition", "HasEnemiesInRange", true, true, 0 },
    { kHasHq, kCondition, "Has HQ", "Condition", "HasHq", true, false, 0 },
    { kHasMission, kCondition, "Has mission", "Condition", "HasMission", true, false, 0 },
    { kHasTarget, kCondition, "Has target", "Condition", "HasTarget", true, false, 0 },
    { kIsColumnMode, kCondition, "In column mode", "Condition", "IsColumnMode", true, false, 0 },
    { kIsFormationMode, kCondition, "In formation mode", "Condition", "IsFormationMode", true, false, 0 },
    { kIsFullStrength, kCondition, "Is full strength", "Condition", "IsFullStrength", true, false, 0 },
    { kIsHalfStrength, kCondition, "Is half strength", "Condition", "IsHalfStrength", true, false, 0 },
    { kIsHq, kCondition, "Is HQ", "Condition", "IsHq", true, false, 0 },
    { kIsIndirectFireUnit, kCondition, "Is indirect fire unit", "Condition", "IsIndirectFireUnit", true, false, 0 },
    { kIsLowStrength, kCondition, "Is low strength", "Condition", "IsLowStrength", true, false, 0 },
    { kIsSupportUnit, kCondition, "Is support unit", "Condition", "IsSupportUnit", true, false, 0 },
    { kIsUnderFire, kCondition, "Is under fire", "Condition", "IsUnderFire", true, false, 0 },
    { kMorale, kCondition, "Morale over X", "Condition", "IsMmoraleOver", true, true, 0 },
    { kFatigue, kCondition, "Fatigue over X", "Condition", "IsFatigueOver", true, true, 0 },
    { kSeesEnemies, kCondition, "Sees X enemies", "Condition", "SeesEnemies", true, true, 0 },

    // global conditions
    { kAreAllObjectivesHeld, kCondition, "Are all objectives held", "Condition", "AreAllObjectivesHeld", true, false, 0 },
    { kAttackScenario, kCondition, "Is attack scenario", "Condition", "AttackScenario", true, false, 0 },
    { kBeginningOfGame, kCondition, "Is beginning of battle", "Condition", "BeginningOfBattle", true, false, 0 },
    { kDefendScenario, kCondition, "Is defend battle", "Condition", "DefendScenario", true, false, 0 },
    { kFirstTurn, kCondition, "Is first turn", "Condition", "FirstTurn", true, false, 0 },
    { kMeetingScenario, kCondition, "Is meeting engagement battle", "Condition", "MeetingScenario", true, false, 0 },

    // organization conditions
    { kIsHeadquarterAlive, kCondition, "Is headquarter alive", "Condition", "IsHeadquarterAlive", true, false, 0 },
    { kShouldAdvance, kCondition, "Should advance", "Condition", "ShouldAdvance", true, false, 0 },
    { kShouldHold, kCondition, "Should hold", "Condition", "ShouldHold", true, false, 0 },
    { kShouldTakeObjective, kCondition, "Should take objective", "Condition", "ShouldTakeObjective", true, false, 0 },

    // actions
    { kAssault, kAction, "Assault", "Action", "Assault", true, false, 0 },
    { kBombard, kAction, "Bombard", "Action", "Bombard", true, false, 0 },
    { kChangeMode, kAction, "Change mode", "Action", "ChangeMode", true, false, 0 },
    { kFaceNearestEnemy, kAction, "Face nearest enemy", "Action", "FaceNearestEnemy", true, false, 0 },
    { kFallBack, kAction, "Fall back", "Action", "FallBack", true, false, 0 },
    { kFire, kAction, "Fire", "Action", "Fire", true, false, 0 },
    { kHold, kAction, "Hold", "Action", "Hold", true, false, 0 },
    { kMoveForward, kAction, "Move forward", "Action", "MoveForward", true, false, 0 },
    { kRally, kAction, "Rally subordinates", "Action", "Rally", true, false, 0 },
    { kTakeObjective, kAction, "Take objective", "Action", "TakeObjective", true, false, 0 },

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


private:

    void setup () {
        if ( m_data.m_typeText.contains( "X")) {
            QString type = m_data.m_typeText;
            type.replace( "X", QString::number(m_value) );
            setText( 0, type );
        }
        else {
            setText( 0, m_data.m_typeText );
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

    int m_id;
    static int m_nextId;
    NodeData m_data;
    int m_value;
};


#endif // NODE_TYPES_HPP
