#ifndef GVL_H_
#define GVL_H_

#include <utility>
#include <vector>
#include <unordered_set>
#include <string>
#include <ostream>

namespace gvl {

    struct Property {
        std::string name;
        std::string value;

        Property(std::string name, std::string value)
                : name(std::move(name)), value(std::move(value)) {}
    };

    struct NodeId {
        std::string name;
        std::string port;

        NodeId(std::string name, std::string port = "") :
                name(std::move(name)), port(std::move(port)) {}
    };

    struct Edge {
        NodeId from;
        NodeId to;
        std::vector<Property> properties;

        Edge(NodeId from, NodeId to, std::vector<Property> properties = {})
                : from(std::move(from)), to(std::move(to)),
                  properties(std::move(properties)) {}
    };

    struct Node {
        NodeId id;
        std::vector<Property> properties;

        explicit Node(NodeId id, std::vector<Property> properties = {})
                : id(std::move(id)), properties(std::move(properties)) {}
    };

/*!
 * A class describing the structure of the desired graph for output through GraphViz.
 * All Strings should be alive when RenderDot will be called. Temporary strings are not allowed.
 */
    class Graph {
    public:

        /*!
         * Create empty graph
         * @param graph_name name of created graph
         */
        explicit Graph(std::string graph_name)
                : nodes_(),
                  edges_(),
                  graph_name_(std::move(graph_name)),
                  graph_props_(),
                  common_edge_props_(),
                  common_node_props_() {}

        /*!
         * Add a new node to the list of nodes with default properties
         * @param node name and port.
         */
        void AddNode(const NodeId &node) {
            const std::vector<Property> default_node_properties = {
                    {"label", node.name}};
            nodes_.emplace_back(node, default_node_properties);
        }

        /*!
         * Add a new node to the list of nodes with custom properties
         * @param node name and port.
         */
        void AddNode(const Node &node) {
            nodes_.emplace_back(node);
        }

        /*!
         * Add a new edge to the list of edges with no properties.
         * @param from start of edge
         * @param to end of edge
         */
        void AddEdge(const NodeId &from, const NodeId &to) {
            edges_.emplace_back(from, to);
        }

        /*!
         * Add a property to graph
         * @param name property name
         * @param value property value
         */
        void
        AddGraphProperty(const std::string &name, const std::string &value) {
            graph_props_.emplace_back(name, value);
        }

        /*!
         * Add a common property to edges
         * @param name property name
         * @param value property value
         */
        void AddCommonEdgeProperty(const std::string &name,
                                   const std::string &value) {
            common_edge_props_.emplace_back(name, value);
        }

        /*!
         * Add a common property to nodes
         * @param name property name
         * @param value property value
         */
        void AddCommonNodeProperty(const std::string &name,
                                   const std::string &value) {
            common_node_props_.emplace_back(name, value);
        }

        /*!
         * Write graph to file in DOT language format.
         * @param out output stream to write
         */
        void RenderDot(std::ostream &out) const;

    private:
        void PrintCommonProperties(std::ostream &out) const;

    private:
        std::vector<Node> nodes_;
        std::vector<Edge> edges_;
        std::string graph_name_;
        std::vector<Property> graph_props_;
        std::vector<Property> common_edge_props_;
        std::vector<Property> common_node_props_;
    };

} // namespace gvl


#endif // GVL_H_