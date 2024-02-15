

class Solution:
    def isSymmetric(self, root: Optional[TreeNode]) -> bool:
        if not root:
            return True
        else:
            return self.isMirror(root.left, root.right)

    def isMirror(self, leftroot, rightroot):
        # if leftroot and rightroot is not none
        if leftroot and rightroot:
            return leftroot.val == rightroot.val and self.isMirror(leftroot.left, rightroot.right) and self.isMirror(leftroot.right, rightroot.left)
        else:
            return leftroot == rightroot
