use std::collections::{HashMap, HashSet};

#[derive(Clone)]
struct Node {
    node_id: String,
}

#[derive(Clone, PartialEq, Eq, Hash)]
enum Direction {
    North,
    South,
    East,
    West,
}

struct Graph {
    nodes: HashMap<String, Node>,
    edges: HashMap<String, HashSet<(String, Direction)>>,
}

impl Graph {
    fn new() -> Self {
        Graph {
            nodes: Vec::new(),
            edges: HashMap::new(),
        }
    }

    fn add_node(&mut self, node_id: &str) {
        if self.nodes.contains_key(&node_id.to_string()) {return}

        let node = Node {node_id: node_id.to_string()};

        self.nodes.insert(node_id.to_string(), node);
        self.edges.entry(node_id.to_string()).or_insert(HashSet::new());
    }

    fn connect(&mut self, node1_id: &str, node2_id: &str, direction: Direction) {
        // Connect node1 to node2 with the specified direction
        if let Some(connections) = self.edges.get_mut(node1_id) {
            connections.insert((node2_id.to_string(), direction.clone()));
        }
        // Connect node2 back to node1 in the opposite direction (optional, if it's a bidirectional graph)
        if let Some(connections) = self.edges.get_mut(node2_id) {
            let opposite_direction = match direction {
                Direction::North => Direction::South,
                Direction::South => Direction::North,
                Direction::East => Direction::West,
                Direction::West => Direction::East,
            };
            connections.insert((node1_id.to_string(), opposite_direction));
        }
    }

    fn get_connections(&self, node_id: &str) -> Option<&HashSet<(String, Direction)>> {
        self.edges.get(node_id)
    }
}

fn main() {
    let mut graph = Graph::new();

    //MAP NODES

    //Warehouses

    //Outgoing warehouses
    //Entances
    graph.add_node("node_ent_ow_A");                //0
    graph.add_node("node_ent_ow_B");                //1
    graph.add_node("node_ent_ow_C");                //2
    graph.add_node("node_ent_ow_D");                //3
    //Warehouses
    graph.add_node("node_ow_A");                    //4
    graph.add_node("node_ow_B");                    //5
    graph.add_node("node_ow_C");                    //6
    graph.add_node("node_ow_D");                    //7

    //Incoming warehouses
    //Entances   
    graph.add_node("node_ent_iw_A");                //8
    graph.add_node("node_ent_iw_B");                //9
    graph.add_node("node_ent_iw_C");                //10
    graph.add_node("node_ent_iw_D");                //11
    //Warehouses
    graph.add_node("node_iw_A");                    //12
    graph.add_node("node_iw_B");                    //13
    graph.add_node("node_iw_C");                    //14
    graph.add_node("node_iw_D");                    //15


    //Machines

    //Machine A
    //Machine Input
    graph.add_node("node_mi_A1");                   //16
    graph.add_node("node_mi_A2");                   //17
    //Machine Output
    graph.add_node("node_mo_A1");                   //18
    graph.add_node("node_mo_A2");                   //19
    //Entrances Input
    graph.add_node("node_mi_ent_A1");               //20
    graph.add_node("node_mi_ent_A2");               //21
    //Entrance Output A1
    graph.add_node("node_mo_ent_A1");               //22

    //Machine B
    //Machine Input
    graph.add_node("node_mi_B1");                   //23
    graph.add_node("node_mi_B2");                   //24
    //Machine Output
    graph.add_node("node_mo_B1");                   //25
    graph.add_node("node_mo_B2");                   //26
    //Entrance Input B2
    graph.add_node("node_mi_ent_B2");               //27
    //Entrances Output
    graph.add_node("node_mo_ent_B1");               //28
    graph.add_node("node_mo_ent_B2");               //29

    //Entrance Output A2 / Entrance Input B1
    graph.add_node("node_mo_ent_A2_mi_ent_B1");     //30

    //Other
    graph.add_node("node_s");                       //31
    graph.add_node("node_m_s");                     //32

    graph.add_node("node_m_e");                     //33
    graph.add_node("node_e");                       //34


    //MAP CONNECTIONS

    graph.connect("firstnode", "secondnode", Direction::North);
    graph.connect("firstnode", "thirdnode", Direction::East);


    if let Some(connections) = graph.get_connections("firstnode") {
        println!("Connections of 'firstnode': {:?}", connections);
    }
}
