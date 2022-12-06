// Implementing Red-Black Tree in C++

#include <iostream>
using namespace std;

struct Node {
  int data;
  Node *parent;
  Node *left;
  Node *right;
  int color;
};

typedef Node *NodePtr;

class RedBlackTree {
   private:
  NodePtr root;
  NodePtr TNULL;

  void initializeNULLNode(NodePtr node, NodePtr parent) {
    node->data = 0;
    node->parent = parent;
    node->left = nullptr;
    node->right = nullptr;
    node->color = 0;
  }

  // Preorder
  void preOrderHelper(NodePtr node) {
    if (node != TNULL) {
      cout << node->data << " ";
      preOrderHelper(node->left);
      preOrderHelper(node->right);
    }
  }

  // Inorder
  void inOrderHelper(NodePtr node) {
    if (node != TNULL) {
      inOrderHelper(node->left);
      cout << node->data << " ";
      inOrderHelper(node->right);
    }
  }

  // Post order
  void postOrderHelper(NodePtr node) {
    if (node != TNULL) {
      postOrderHelper(node->left);
      postOrderHelper(node->right);
      cout << node->data << " ";
    }
  }

  NodePtr searchTreeHelper(NodePtr node, int key) {
    if (node == TNULL || key == node->data) {
      return node;
    }

    if (key < node->data) {
      return searchTreeHelper(node->left, key);
    }
    return searchTreeHelper(node->right, key);
  }

  // For balancing the tree after deletion
  void deleteFix(NodePtr x) {
    NodePtr s;
    while (x != root && x->color == 0) {
      if (x == x->parent->left) {
        s = x->parent->right;
        if (s->color == 1) {
          s->color = 0;
          x->parent->color = 1;
          leftRotate(x->parent);
          s = x->parent->right;
        }

        if (s->left->color == 0 && s->right->color == 0) {
          s->color = 1;
          x = x->parent;
        } else {
          if (s->right->color == 0) {
            s->left->color = 0;
            s->color = 1;
            rightRotate(s);
            s = x->parent->right;
          }

          s->color = x->parent->color;
          x->parent->color = 0;
          s->right->color = 0;
          leftRotate(x->parent);
          x = root;
        }
      } else {
        s = x->parent->left;
        if (s->color == 1) {
          s->color = 0;
          x->parent->color = 1;
          rightRotate(x->parent);
          s = x->parent->left;
        }

        if (s->right->color == 0 && s->right->color == 0) {
          s->color = 1;
          x = x->parent;
        } else {
          if (s->left->color == 0) {
            s->right->color = 0;
            s->color = 1;
            leftRotate(s);
            s = x->parent->left;
          }

          s->color = x->parent->color;
          x->parent->color = 0;
          s->left->color = 0;
          rightRotate(x->parent);
          x = root;
        }
      }
    }
    x->color = 0;
  }

  void rbTransplant(NodePtr u, NodePtr v) {
    if (u->parent == nullptr) {
      root = v;
    } else if (u == u->parent->left) {
      u->parent->left = v;
    } else {
      u->parent->right = v;
    }
    v->parent = u->parent;
  }

  void deleteNodeHelper(NodePtr node, int key) {
    NodePtr z = TNULL;
    NodePtr x, y;
    while (node != TNULL) {
      if (node->data == key) {
        z = node;
      }

      if (node->data <= key) {
        node = node->right;
      } else {
        node = node->left;
      }
    }

    if (z == TNULL) {
      cout << "Key not found in the tree" << endl;
      return;
    }

    y = z;
    int y_original_color = y->color;
    if (z->left == TNULL) {
      x = z->right;
      rbTransplant(z, z->right);
    } else if (z->right == TNULL) {
      x = z->left;
      rbTransplant(z, z->left);
    } else {
      y = minimum(z->right);
      y_original_color = y->color;
      x = y->right;
      if (y->parent == z) {
        x->parent = y;
      } else {
        rbTransplant(y, y->right);
        y->right = z->right;
        y->right->parent = y;
      }

      rbTransplant(z, y);
      y->left = z->left;
      y->left->parent = y;
      y->color = z->color;
    }
    delete z;
    if (y_original_color == 0) {
      deleteFix(x);
    }
  }

  // For balancing the tree after insertion
  void insertFix(NodePtr k) {
    NodePtr u;
    while (k->parent->color == 1) {
      if (k->parent == k->parent->parent->right) {
        u = k->parent->parent->left;
        if (u->color == 1) {
          u->color = 0;
          k->parent->color = 0;
          k->parent->parent->color = 1;
          k = k->parent->parent;
        } else {
          if (k == k->parent->left) {
            k = k->parent;
            rightRotate(k);
          }
          k->parent->color = 0;
          k->parent->parent->color = 1;
          leftRotate(k->parent->parent);
        }
      } else {
        u = k->parent->parent->right;

        if (u->color == 1) {
          u->color = 0;
          k->parent->color = 0;
          k->parent->parent->color = 1;
          k = k->parent->parent;
        } else {
          if (k == k->parent->right) {
            k = k->parent;
            leftRotate(k);
          }
          k->parent->color = 0;
          k->parent->parent->color = 1;
          rightRotate(k->parent->parent);
        }
      }
      if (k == root) {
        break;
      }
    }
    root->color = 0;
  }

  void printHelper(NodePtr root, string indent, bool last) {
    if (root != TNULL) {
      cout << indent;
      if (last) {
        cout << "R----";
        indent += "   ";
      } else {
        cout << "L----";
        indent += "|  ";
      }

      string sColor = root->color ? "RED" : "BLACK";
      cout << root->data << "(" << sColor << ")" << endl;
      printHelper(root->left, indent, false);
      printHelper(root->right, indent, true);
    }
  }

   public:
  RedBlackTree() {
    TNULL = new Node;
    TNULL->color = 0;
    TNULL->left = nullptr;
    TNULL->right = nullptr;
    root = TNULL;
  }

  void preorder() {
    preOrderHelper(this->root);
  }

  void inorder() {
    inOrderHelper(this->root);
  }

  void postorder() {
    postOrderHelper(this->root);
  }

  NodePtr searchTree(int k) {
    return searchTreeHelper(this->root, k);
  }

  NodePtr minimum(NodePtr node) {
    while (node->left != TNULL) {
      node = node->left;
    }
    return node;
  }

  NodePtr maximum(NodePtr node) {
    while (node->right != TNULL) {
      node = node->right;
    }
    return node;
  }

  NodePtr successor(NodePtr x) {
    if (x->right != TNULL) {
      return minimum(x->right);
    }

    NodePtr y = x->parent;
    while (y != TNULL && x == y->right) {
      x = y;
      y = y->parent;
    }
    return y;
  }

  NodePtr predecessor(NodePtr x) {
    if (x->left != TNULL) {
      return maximum(x->left);
    }

    NodePtr y = x->parent;
    while (y != TNULL && x == y->left) {
      x = y;
      y = y->parent;
    }

    return y;
  }

  void leftRotate(NodePtr x) {
    NodePtr y = x->right;
    x->right = y->left;
    if (y->left != TNULL) {
      y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
      this->root = y;
    } else if (x == x->parent->left) {
      x->parent->left = y;
    } else {
      x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
  }

  void rightRotate(NodePtr x) {
    NodePtr y = x->left;
    x->left = y->right;
    if (y->right != TNULL) {
      y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
      this->root = y;
    } else if (x == x->parent->right) {
      x->parent->right = y;
    } else {
      x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
  }

  // Inserting a node
  void insert(int key) {
    NodePtr node = new Node;
    node->parent = nullptr;
    node->data = key;
    node->left = TNULL;
    node->right = TNULL;
    node->color = 1;

    NodePtr y = nullptr;
    NodePtr x = this->root;

    while (x != TNULL) {
      y = x;
      if (node->data < x->data) {
        x = x->left;
      } else {
        x = x->right;
      }
    }

    node->parent = y;
    if (y == nullptr) {
      root = node;
    } else if (node->data < y->data) {
      y->left = node;
    } else {
      y->right = node;
    }

    if (node->parent == nullptr) {
      node->color = 0;
      return;
    }

    if (node->parent->parent == nullptr) {
      return;
    }

    insertFix(node);
  }

  NodePtr getRoot() {
    return this->root;
  }

  void deleteNode(int data) {
    deleteNodeHelper(this->root, data);
  }

  void printTree() {
    if (root) {
      printHelper(this->root, "", true);
    }
  }
};

int main() {
  RedBlackTree bst;
  bst.insert(55);
  bst.insert(40);
  bst.insert(65);
  bst.insert(60);
  bst.insert(75);
  bst.insert(57);

  bst.printTree();
  cout << endl
     << "After deleting" << endl;
  bst.deleteNode(40);
  bst.printTree();
}



#ifndef MAP_HPP
# define MAP_HPP

# include <memory>
# include <iterator>
# include <algorithm>

# include "RBTree.hpp"
# include "enable_if.hpp"
# include "vector_iterator.hpp"
# include "equal.hpp"
# include "pair.hpp"

namespace ft
{
	template <	class Key,
                class T,
                class Compare = std::less< Key >,
                class Alloc = std::allocator< ft::pair< const Key, T > >
             >
			 		 
	class map
	{
		// [ MEMBER TYPES ]
		public:
			class 												value_compare; // defined on line 71

			typedef Key                                         			key_type;
			typedef	T			 											mapped_type;
            typedef ft::pair< const Key, T >     							value_type;
			typedef Compare                                     			key_compare;
			typedef Alloc													allocator_type;
            
		private:
			typedef RBTree<value_type, value_compare, allocator_type>		rbtree;

		public:
			typedef typename allocator_type::reference          reference;
			typedef typename allocator_type::const_reference   	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;

			typedef typename rbtree::iterator					iterator;
			typedef typename rbtree::const_iterator				const_iterator;
			typedef ft::reverse_iterator< iterator >			reverse_iterator;
			typedef ft::reverse_iterator< const_iterator >		const_reverse_iterator;
			typedef typename iterator_traits<iterator>::difference_type		difference_type;
			typedef size_t													size_type;
			typedef node< value_type >                          treeNode;
			

		private:
			rbtree												_tree;
			key_compare											_compare;
			allocator_type										_alloc;
		
		public:
			// [ MEMBER CLASSES ]
			class value_compare
			{   
				friend class map;
				protected:
					key_compare		comp;
					value_compare 	(key_compare c) : comp(c) {}  // constructed with map's comparison object
					
				public:
					typedef bool 			result_type;
					typedef value_type 		first_argument_type;
					typedef value_type 		second_argument_type;
					bool 	operator() ( const value_type& x, const value_type& y ) const 			
          { 		return comp(x.first, y.first);			};
			};

			// [ MEMEBER FUNCTIONS ]
			explicit map( const key_compare & comp = key_compare(),
						const allocator_type & alloc = allocator_type()) :	_tree(comp, alloc),
																			_compare(comp),
																			_alloc(alloc) {};

			map( map const& m ):	_tree(m._tree),
									_compare(m._compare),
									_alloc(m._alloc) {};
			
			template < typename InputIterator >
			map(	InputIterator first, InputIterator last, 
					key_compare const & comp = key_compare(),
					allocator_type const & alloc = allocator_type()):		_tree(comp, alloc),
																			_compare(comp)				{	_tree.insert(first, last);	};

			virtual ~map() {};
			
			map& operator = ( map const& m)
			{
				if (this != &m)
				{
					_tree = m._tree;
					_compare = m._compare;
					_alloc = m._alloc ;
				}
				return *this;
			}

			// [ ITERATORS ]
			iterator 			begin()									
      {	return	_tree.begin();		};
			
      const_iterator		begin() const							
      {	return	_tree.begin();		};
			
      iterator 			end()									
      {	return	_tree.end();		};
			
      const_iterator 		end() const								
      {	return	_tree.end();		};
			
      reverse_iterator		rbegin()							
      {	return	_tree.rbegin();		};
			
      const_reverse_iterator 	rbegin() const						
      {	return	_tree.rbegin();		};
			
      reverse_iterator 		rend()								
      {	return	_tree.rend();		};
			
      const_reverse_iterator 	rend() const						
      {	return	_tree.rend();		};


			// [ CAPACITY ]
			bool			empty( void ) const							
      {	return	_tree.empty();		};
			
      size_type 		size( void ) const							
      {	return	_tree.size();		};
			
      size_type 		max_size() const							
      {	return	_tree.max_size();	};


			// [ ELEMENT ACCESS ]
			mapped_type& 	operator[] ( const key_type& k )			
      {	return (*(insert(ft::make_pair( k, mapped_type() )).first)).second;			};


			// [ MODIFIERS ]
			ft::pair< iterator,bool > 	insert(value_type const & val)						
      {	return _tree.insert( val );					};
			
      iterator 					insert(iterator position, const value_type& val)	
      {	return _tree.insert( position, val );		};
			
      template <class InputIterator>
  			void 						insert (InputIterator first, InputIterator last) 
        {	_tree.insert(first, last);	};

			void 						erase(iterator position)						
      {	_tree.erase( position.base() );				};
			
      size_type 					erase(const key_type& k)							
      {	return _tree.erase( get_valuetype(k) );		};
			
      void 						erase(iterator first, iterator last)		
      {	_tree.erase( first, last );					};

			void 						swap(map& m)										
      {	_tree.swap(m._tree);						};

			void 						clear()											
      {	_tree.clear(_tree.get_root());				};
			
			// [ OBSERVERS ]
			key_compare 				key_comp() const									
      {	return this->_compare;											};
			
      value_compare 				value_comp() const									
      {	return value_compare(this->_compare);							};


			// [ OPERATIONS ]
			iterator					find(const key_type& k)								
      {	return _tree.find(get_valuetype(k));			};
			
      const_iterator				find(const key_type& k) const						
      {	return _tree.find(get_valuetype(k));			};
			

			size_type 					count(key_type const & k) const						
      {	return _tree.search(_tree.get_root(),get_valuetype(k)) ? 1 : 0;	};


			iterator 					lower_bound(key_type const & k)						
      {	return _tree.lower_bound(get_valuetype(k));		};
			
      iterator 					lower_bound(key_type const & k) const				
      {	return _tree.lower_bound(get_valuetype(k));		};


			iterator 					upper_bound(key_type const & k)						
      {	return _tree.upper_bound(get_valuetype(k));		};
			
      iterator 					upper_bound(key_type const & k) const				
      {	return _tree.upper_bound(get_valuetype(k));		};


			ft::pair< iterator, iterator >             equal_range (const key_type& k)			
      {	return (ft::make_pair(lower_bound(k), upper_bound(k)));	};
			
      ft::pair< const_iterator, const_iterator > equal_range (const key_type& k) const	
      {	return (ft::make_pair(lower_bound(k), upper_bound(k)));	};



			// [ ALLOCATOR ]
			allocator_type	get_allocator( void ) const									
      {	return _tree.get_allocator();	};
			

		private:
			// [ HELPER FUNCTIONS ]
			value_type				get_valuetype( const key_type& k ) const			
      {		return ft::make_pair( k, mapped_type() );					};
			
      void					inorder( void ) 									
      {		_tree.inorder(_tree.get_root());							};

	};
	
	// [ NON MEMBER FUNCTIONS ]
	template <class T, class Alloc>
	bool	operator == ( const map< T, Alloc >& l, const map< T, Alloc >& r ) 
	{
		if (l.size() != r.size())	return false;
		return ft::equal(l.begin(), l.end(), r.begin());
	};

	template <class T, class Alloc>
	bool	operator !=  ( const map< T, Alloc >& l, const map< T, Alloc >& r )		
  {	return !(l == r);	}


	template <class T, class Alloc>
	bool	operator <  ( const map< T, Alloc >& l, const map< T, Alloc >& r )		
  {	return ft::lexicographical_compare(l.begin(), l.end(), r.begin(), r.end());		}


	template <class T, class Alloc>
	bool	operator <=  ( const map< T, Alloc >& l, const map< T, Alloc >& r )		
  {	return !(r < l);	}


	template <class T, class Alloc>
	bool	operator >  ( const map< T, Alloc >& l, const map< T, Alloc >& r )		
  {	return r < l;		}


	template <class T, class Alloc>
	bool	operator >=  ( const map< T, Alloc >& l, const map< T, Alloc >& r )		
  {	return !(l < r);	}


	template <class T, class Alloc>
	void	swap( map< T, Alloc >& x, map< T, Alloc >& y) 							{	x.swap(y);			}
};

#endif

./rbt.hpp:422:12: error: no matching function for call to object of type
'ft::rbt<ft::pair<const int, int>, std::__1::less<int>, std::__1::allocator<ft::pair<const int,
      int> > >::value_compare' (aka 'std::__1::less<int>')
                                                if (!_comp(tmp->value, new_node->value) && !_comp(new_node->value, tmp->value))