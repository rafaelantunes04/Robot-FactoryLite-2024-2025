

pub fn get_node_id(key: &str) -> Option<u8> {
    match key {
        "node_ent_ow_A" => Some(0),
        "node_ent_ow_B" => Some(1),
        "node_ent_ow_C" => Some(2),
        "node_ent_ow_D" => Some(3),
        "node_ow_A" => Some(4),
        "node_ow_B" => Some(5),
        "node_ow_C" => Some(6),
        "node_ow_D" => Some(7),
        "node_ent_iw_A" => Some(8),
        "node_ent_iw_B" => Some(9),
        "node_ent_iw_C" => Some(10),
        "node_ent_iw_D" => Some(11),
        "node_iw_A" => Some(12),
        "node_iw_B" => Some(13),
        "node_iw_C" => Some(14),
        "node_iw_D" => Some(15),
        "node_mi_A1" => Some(16),
        "node_mi_A2" => Some(17),
        "node_mo_A1" => Some(18),
        "node_mo_A2" => Some(19),
        "node_mi_ent_A1" => Some(20),
        "node_mi_ent_A2" => Some(21),
        "node_mo_ent_A1" => Some(22),
        "node_mi_B1" => Some(23),
        "node_mi_B2" => Some(24),
        "node_mo_B1" => Some(25),
        "node_mo_B2" => Some(26),
        "node_mi_ent_B2" => Some(27),
        "node_mo_ent_B1" => Some(28),
        "node_mo_ent_B2" => Some(29),
        "node_mo_ent_A2_mi_ent_B1" => Some(30),
        "node_s" => Some(31),
        "node_m_s" => Some(32),
        "node_m_e" => Some(33),
        "node_e" => Some(34),
        _ => None,
    }
}

pub fn get_node_name(value: u8) -> Option<&'static str> {
    match value {
        0 => Some("node_ent_ow_A"),
        1 => Some("node_ent_ow_B"),
        2 => Some("node_ent_ow_C"),
        3 => Some("node_ent_ow_D"),
        4 => Some("node_ow_A"),
        5 => Some("node_ow_B"),
        6 => Some("node_ow_C"),
        7 => Some("node_ow_D"),
        8 => Some("node_ent_iw_A"),
        9 => Some("node_ent_iw_B"),
        10 => Some("node_ent_iw_C"),
        11 => Some("node_ent_iw_D"),
        12 => Some("node_iw_A"),
        13 => Some("node_iw_B"),
        14 => Some("node_iw_C"),
        15 => Some("node_iw_D"),
        16 => Some("node_mi_A1"),
        17 => Some("node_mi_A2"),
        18 => Some("node_mo_A1"),
        19 => Some("node_mo_A2"),
        20 => Some("node_mi_ent_A1"),
        21 => Some("node_mi_ent_A2"),
        22 => Some("node_mo_ent_A1"),
        23 => Some("node_mi_B1"),
        24 => Some("node_mi_B2"),
        25 => Some("node_mo_B1"),
        26 => Some("node_mo_B2"),
        27 => Some("node_mi_ent_B2"),
        28 => Some("node_mo_ent_B1"),
        29 => Some("node_mo_ent_B2"),
        30 => Some("node_mo_ent_A2_mi_ent_B1"),
        31 => Some("node_s"),
        32 => Some("node_m_s"),
        33 => Some("node_m_e"),
        34 => Some("node_e"),
        _ => None,
    }
}

#[derive(Clone)]
enum Direction {
    North,
    South,
    East,
    West,
}

#[derive(Clone)]
struct Connection {
    destination: u8,
    direction: Direction,
    weight: u8,
}

impl Connection {
    fn new(_destination: u8, _direction: Direction, _weight: u8) -> Self {
        Connection { destination: _destination, direction: _direction, weight: _weight }
    }

    fn reverse(&self, origin: u8) -> Self {
        let opposite_direction = match self.direction {
            Direction::North => Direction::South,
            Direction::South => Direction::North,
            Direction::East => Direction::West,
            Direction::West => Direction::East,
        };
        Connection::new(origin, opposite_direction, self.weight)
    }
}

struct Node {
    id: u8,
    connections: Vec<Connection>
}

impl Node {
    fn new(_id: u8) -> Self {
        Node { id: _id, connections: Vec::<Connection>::new() }
    }
    
    fn connect(&mut self, connection: Connection) {
        self.connections.push(connection)
    }

    fn has_connection(&self, destination: u8) -> bool {
        self.connections.iter().any(|conn| conn.destination == destination)
    }

    fn get_connections(&self) -> Vec<u8>{
        self.connections.iter().map(|conn| conn.destination).collect()
    }
}

struct Graph {
    nodes: Vec<Node>
}

impl Graph {
    fn new() -> Self {
        Graph { nodes: Vec::<Node>::new() }
    }

    fn get(&self, index: u8) -> &Node {
        self.nodes.get(index as usize).unwrap()
    }

    fn get_mut(&mut self, index: u8) -> &mut Node {
        self.nodes.get_mut(index as usize).unwrap()
    }

    fn connect(&mut self, origin: u8, connection: Connection) {
        if self.nodes.get(origin as usize).unwrap().has_connection(connection.destination) {
            return
        }

        self.get_mut(origin).connect(connection.clone());
        
        self.get_mut(connection.destination).connect(connection.reverse(origin));
    }
}

fn create_graph(qty_nodes: u8) -> Graph {
    let mut graph: Graph = Graph::new();
    for i in 0..=qty_nodes {
        graph.nodes.push(Node::new(i));
    }
    return graph;
}

fn main() {
    let mut graph = create_graph(34);
    let connection = Connection::new(32, Direction::East, 3);
    graph.connect(31, connection);
    
    let current_node = graph.get(31);

    println!("{}", get_node_name(current_node.id).unwrap());
    for i in current_node.get_connections() {
        println!("{}", i)
    }
}
